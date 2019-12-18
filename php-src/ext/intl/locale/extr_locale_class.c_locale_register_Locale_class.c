#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * create_object; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  INIT_CLASS_ENTRY (TYPE_1__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Locale_ce_ptr ; 
 int /*<<< orphan*/  Locale_class_functions ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_register_internal_class (TYPE_1__*) ; 

void locale_register_Locale_class( void )
{
	zend_class_entry ce;

	/* Create and register 'Locale' class. */
	INIT_CLASS_ENTRY( ce, "Locale", Locale_class_functions );
	ce.create_object = NULL;
	Locale_ce_ptr = zend_register_internal_class( &ce );

	/* Declare 'Locale' class properties. */
	if( !Locale_ce_ptr )
	{
		zend_error( E_ERROR,
			"Locale: Failed to register Locale class.");
		return;
	}
}