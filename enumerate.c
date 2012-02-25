#include <stdio.h>

#include "tempered.h"

void print_error( char *error )
{
	fprintf( stderr, "%s\n", error );
}

int main( int argc, char **argv )
{
	char *error = NULL;
	if ( !tempered_init( &error ) )
	{
		print_error( error );
		return 1;
	}
	
	struct tempered_device_list *list = tempered_enumerate( &error );
	if ( list == NULL )
	{
		print_error( error );
	}
	else
	{
		struct tempered_device_list *dev;
		for ( dev = list ; dev != NULL ; dev = dev->next )
		{
			printf(
				"Found device: %04x:%04x %i | %s | %s\n",
				dev->type->vendor_id, dev->type->product_id,
				dev->type->interface_number,
				dev->path,
				dev->type->name
			);
		}
		
		tempered_free_device_list( list );
	}
	
	if ( !tempered_exit( &error ) )
	{
		print_error( error );
		return 1;
	}
	return 0;
}
