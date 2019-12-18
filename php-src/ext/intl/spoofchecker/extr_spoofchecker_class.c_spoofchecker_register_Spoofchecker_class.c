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
struct TYPE_7__ {int /*<<< orphan*/  free_obj; int /*<<< orphan*/  clone_obj; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CLASS_ENTRY (TYPE_1__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Spoofchecker_ce_ptr ; 
 int /*<<< orphan*/  Spoofchecker_class_functions ; 
 TYPE_3__ Spoofchecker_handlers ; 
 int /*<<< orphan*/  Spoofchecker_object ; 
 int /*<<< orphan*/  Spoofchecker_object_create ; 
 int /*<<< orphan*/  Spoofchecker_objects_free ; 
 int /*<<< orphan*/  XtOffsetOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spoofchecker_clone_obj ; 
 int /*<<< orphan*/  std_object_handlers ; 
 int /*<<< orphan*/  zend_register_internal_class (TYPE_1__*) ; 
 int /*<<< orphan*/  zo ; 

void spoofchecker_register_Spoofchecker_class(void)
{
	zend_class_entry ce;

	/* Create and register 'Spoofchecker' class. */
	INIT_CLASS_ENTRY(ce, "Spoofchecker", Spoofchecker_class_functions);
	ce.create_object = Spoofchecker_object_create;
	Spoofchecker_ce_ptr = zend_register_internal_class(&ce);

	memcpy(&Spoofchecker_handlers, &std_object_handlers,
		sizeof Spoofchecker_handlers);
	Spoofchecker_handlers.offset = XtOffsetOf(Spoofchecker_object, zo);
	Spoofchecker_handlers.clone_obj = spoofchecker_clone_obj;
	Spoofchecker_handlers.free_obj = Spoofchecker_objects_free;
}