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
 int /*<<< orphan*/  Normalizer_ce_ptr ; 
 int /*<<< orphan*/  Normalizer_class_functions ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_register_internal_class (TYPE_1__*) ; 

void normalizer_register_Normalizer_class( void )
{
	zend_class_entry ce;

	/* Create and register 'Normalizer' class. */
	INIT_CLASS_ENTRY( ce, "Normalizer", Normalizer_class_functions );
	ce.create_object = NULL;
	Normalizer_ce_ptr = zend_register_internal_class( &ce );

	/* Declare 'Normalizer' class properties. */
	if( !Normalizer_ce_ptr )
	{
		zend_error( E_ERROR,
			"Normalizer: attempt to create properties "
			"on a non-registered class." );
		return;
	}
}