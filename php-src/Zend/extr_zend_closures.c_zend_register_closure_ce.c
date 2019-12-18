#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_handlers ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_6__ {int /*<<< orphan*/  get_gc; int /*<<< orphan*/  get_closure; int /*<<< orphan*/  get_debug_info; int /*<<< orphan*/  clone_obj; int /*<<< orphan*/  compare; int /*<<< orphan*/  unset_property; int /*<<< orphan*/  has_property; int /*<<< orphan*/  get_property_ptr_ptr; int /*<<< orphan*/  read_property; int /*<<< orphan*/  write_property; int /*<<< orphan*/  get_method; int /*<<< orphan*/  get_constructor; int /*<<< orphan*/  free_obj; } ;
struct TYPE_5__ {int /*<<< orphan*/  unserialize; int /*<<< orphan*/  serialize; int /*<<< orphan*/  create_object; int /*<<< orphan*/  ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CLASS_ENTRY (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_ACC_FINAL ; 
 int /*<<< orphan*/  closure_functions ; 
 TYPE_3__ closure_handlers ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  std_object_handlers ; 
 TYPE_1__* zend_ce_closure ; 
 int /*<<< orphan*/  zend_class_serialize_deny ; 
 int /*<<< orphan*/  zend_class_unserialize_deny ; 
 int /*<<< orphan*/  zend_closure_clone ; 
 int /*<<< orphan*/  zend_closure_compare ; 
 int /*<<< orphan*/  zend_closure_free_storage ; 
 int /*<<< orphan*/  zend_closure_get_closure ; 
 int /*<<< orphan*/  zend_closure_get_constructor ; 
 int /*<<< orphan*/  zend_closure_get_debug_info ; 
 int /*<<< orphan*/  zend_closure_get_gc ; 
 int /*<<< orphan*/  zend_closure_get_method ; 
 int /*<<< orphan*/  zend_closure_get_property_ptr_ptr ; 
 int /*<<< orphan*/  zend_closure_has_property ; 
 int /*<<< orphan*/  zend_closure_new ; 
 int /*<<< orphan*/  zend_closure_read_property ; 
 int /*<<< orphan*/  zend_closure_unset_property ; 
 int /*<<< orphan*/  zend_closure_write_property ; 
 TYPE_1__* zend_register_internal_class (int /*<<< orphan*/ *) ; 

void zend_register_closure_ce(void) /* {{{ */
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "Closure", closure_functions);
	zend_ce_closure = zend_register_internal_class(&ce);
	zend_ce_closure->ce_flags |= ZEND_ACC_FINAL;
	zend_ce_closure->create_object = zend_closure_new;
	zend_ce_closure->serialize = zend_class_serialize_deny;
	zend_ce_closure->unserialize = zend_class_unserialize_deny;

	memcpy(&closure_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	closure_handlers.free_obj = zend_closure_free_storage;
	closure_handlers.get_constructor = zend_closure_get_constructor;
	closure_handlers.get_method = zend_closure_get_method;
	closure_handlers.write_property = zend_closure_write_property;
	closure_handlers.read_property = zend_closure_read_property;
	closure_handlers.get_property_ptr_ptr = zend_closure_get_property_ptr_ptr;
	closure_handlers.has_property = zend_closure_has_property;
	closure_handlers.unset_property = zend_closure_unset_property;
	closure_handlers.compare = zend_closure_compare;
	closure_handlers.clone_obj = zend_closure_clone;
	closure_handlers.get_debug_info = zend_closure_get_debug_info;
	closure_handlers.get_closure = zend_closure_get_closure;
	closure_handlers.get_gc = zend_closure_get_gc;
}