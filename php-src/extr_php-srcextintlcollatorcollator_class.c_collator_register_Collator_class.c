#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  create_object; } ;
typedef  TYPE_1__ zend_class_entry ;
struct TYPE_7__ {int /*<<< orphan*/  free_obj; int /*<<< orphan*/ * clone_obj; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  Collator_ce_ptr ; 
 int /*<<< orphan*/  Collator_class_functions ; 
 TYPE_3__ Collator_handlers ; 
 int /*<<< orphan*/  Collator_object ; 
 int /*<<< orphan*/  Collator_object_create ; 
 int /*<<< orphan*/  Collator_objects_free ; 
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  INIT_CLASS_ENTRY (TYPE_1__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtOffsetOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  std_object_handlers ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_register_internal_class (TYPE_1__*) ; 
 int /*<<< orphan*/  zo ; 

void collator_register_Collator_class( void )
{
	zend_class_entry ce;

	/* Create and register 'Collator' class. */
	INIT_CLASS_ENTRY( ce, "Collator", Collator_class_functions );
	ce.create_object = Collator_object_create;
	Collator_ce_ptr = zend_register_internal_class( &ce );

	memcpy(&Collator_handlers, &std_object_handlers,
		sizeof Collator_handlers);
	/* Collator has no usable clone semantics - ucol_cloneBinary/ucol_openBinary require binary buffer
	   for which we don't have the place to keep */
	Collator_handlers.offset = XtOffsetOf(Collator_object, zo);
	Collator_handlers.clone_obj = NULL;
	Collator_handlers.free_obj = Collator_objects_free;

	/* Declare 'Collator' class properties. */
	if( !Collator_ce_ptr )
	{
		zend_error( E_ERROR,
			"Collator: attempt to create properties "
			"on a non-registered class." );
		return;
	}
}