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
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/ * EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/ * Transliterator_ce_ptr ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fake_scope ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zend_binary_strcmp (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_get_executed_scope () ; 
 int /*<<< orphan*/ * zend_std_write_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static zval *Transliterator_write_property( zend_object *object, zend_string *name, zval *value,
	void **cache_slot )
{
	zend_class_entry *scope;

	if (EG(fake_scope)) {
		scope = EG(fake_scope);
	} else {
		scope = zend_get_executed_scope();
	}
	if( ( scope != Transliterator_ce_ptr ) &&
		( zend_binary_strcmp( "id", sizeof( "id" ) - 1,
		ZSTR_VAL( name ), ZSTR_LEN( name ) ) == 0 ) )
	{
		php_error_docref(NULL, E_WARNING, "The property \"id\" is read-only" );
	}
	else
	{
		value = zend_std_write_property( object, name, value, cache_slot );
	}

	return value;
}