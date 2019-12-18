#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_binary_strcmp (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_std_get_property_ptr_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void**) ; 

__attribute__((used)) static zval *Transliterator_get_property_ptr_ptr( zend_object *object, zend_string *name, int type, void **cache_slot )
{
	zval *retval;

	if(zend_binary_strcmp( "id", sizeof( "id" ) - 1,
		ZSTR_VAL( name ), ZSTR_LEN( name ) ) == 0 )
	{
		retval = NULL; /* fallback to read_property */
	}
	else
	{
		retval = zend_std_get_property_ptr_ptr( object, name, type, cache_slot );
	}

	return retval;
}