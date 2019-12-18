#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_handlers ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_6__ {int /*<<< orphan*/  unserialize; int /*<<< orphan*/  serialize; int /*<<< orphan*/  create_object; int /*<<< orphan*/  ce_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/ * clone_obj; int /*<<< orphan*/  get_property_ptr_ptr; int /*<<< orphan*/  unset_property; int /*<<< orphan*/  has_property; int /*<<< orphan*/  write_property; int /*<<< orphan*/  read_property; int /*<<< orphan*/  free_obj; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CLASS_ENTRY (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtOffsetOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_ACC_FINAL ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  std ; 
 TYPE_2__* zend_ce_weakref ; 
 int /*<<< orphan*/  zend_class_serialize_deny ; 
 int /*<<< orphan*/  zend_class_unserialize_deny ; 
 int /*<<< orphan*/  zend_get_std_object_handlers () ; 
 TYPE_2__* zend_register_internal_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_weakref ; 
 int /*<<< orphan*/  zend_weakref_free ; 
 TYPE_1__ zend_weakref_handlers ; 
 int /*<<< orphan*/  zend_weakref_methods ; 
 int /*<<< orphan*/  zend_weakref_new ; 
 int /*<<< orphan*/  zend_weakref_no_isset ; 
 int /*<<< orphan*/  zend_weakref_no_read ; 
 int /*<<< orphan*/  zend_weakref_no_read_ptr ; 
 int /*<<< orphan*/  zend_weakref_no_unset ; 
 int /*<<< orphan*/  zend_weakref_no_write ; 

void zend_register_weakref_ce(void) /* {{{ */
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "WeakReference", zend_weakref_methods);
	zend_ce_weakref = zend_register_internal_class(&ce);
	zend_ce_weakref->ce_flags |= ZEND_ACC_FINAL;

	zend_ce_weakref->create_object = zend_weakref_new;
	zend_ce_weakref->serialize = zend_class_serialize_deny;
	zend_ce_weakref->unserialize = zend_class_unserialize_deny;

	memcpy(&zend_weakref_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	zend_weakref_handlers.offset = XtOffsetOf(zend_weakref, std);

	zend_weakref_handlers.free_obj = zend_weakref_free;
	zend_weakref_handlers.read_property = zend_weakref_no_read;
	zend_weakref_handlers.write_property = zend_weakref_no_write;
	zend_weakref_handlers.has_property = zend_weakref_no_isset;
	zend_weakref_handlers.unset_property = zend_weakref_no_unset;
	zend_weakref_handlers.get_property_ptr_ptr = zend_weakref_no_read_ptr;
	zend_weakref_handlers.clone_obj = NULL;
}