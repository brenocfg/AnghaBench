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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* constructor; int /*<<< orphan*/  name; int /*<<< orphan*/  __debugInfo; int /*<<< orphan*/  destructor; int /*<<< orphan*/  unserialize; int /*<<< orphan*/  unserialize_func; int /*<<< orphan*/  serialize; int /*<<< orphan*/  serialize_func; int /*<<< orphan*/  clone; int /*<<< orphan*/  __tostring; int /*<<< orphan*/  __callstatic; int /*<<< orphan*/  __call; int /*<<< orphan*/  __isset; int /*<<< orphan*/  __unset; int /*<<< orphan*/  __set; int /*<<< orphan*/  __get; scalar_t__ iterator_funcs_ptr; int /*<<< orphan*/  get_iterator; int /*<<< orphan*/  create_object; struct TYPE_7__* parent; } ;
typedef  TYPE_3__ zend_class_entry ;
struct TYPE_5__ {int fn_flags; int /*<<< orphan*/  function_name; } ;
struct TYPE_6__ {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ EXPECTED (int) ; 
 int /*<<< orphan*/  E_ERROR ; 
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_FINAL ; 
 int /*<<< orphan*/  ZEND_ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_inherit_parent_constructor(zend_class_entry *ce) /* {{{ */
{
	zend_class_entry *parent = ce->parent;

	ZEND_ASSERT(parent != NULL);

	/* You cannot change create_object */
	ce->create_object = parent->create_object;

	/* Inherit special functions if needed */
	if (EXPECTED(!ce->get_iterator)) {
		ce->get_iterator = parent->get_iterator;
	}
	if (parent->iterator_funcs_ptr) {
		/* Must be initialized through iface->interface_gets_implemented() */
		ZEND_ASSERT(ce->iterator_funcs_ptr);
	}
	if (EXPECTED(!ce->__get)) {
		ce->__get = parent->__get;
	}
	if (EXPECTED(!ce->__set)) {
		ce->__set = parent->__set;
	}
	if (EXPECTED(!ce->__unset)) {
		ce->__unset = parent->__unset;
	}
	if (EXPECTED(!ce->__isset)) {
		ce->__isset = parent->__isset;
	}
	if (EXPECTED(!ce->__call)) {
		ce->__call = parent->__call;
	}
	if (EXPECTED(!ce->__callstatic)) {
		ce->__callstatic = parent->__callstatic;
	}
	if (EXPECTED(!ce->__tostring)) {
		ce->__tostring = parent->__tostring;
	}
	if (EXPECTED(!ce->clone)) {
		ce->clone = parent->clone;
	}
	if (EXPECTED(!ce->serialize_func)) {
		ce->serialize_func = parent->serialize_func;
	}
	if (EXPECTED(!ce->serialize)) {
		ce->serialize = parent->serialize;
	}
	if (EXPECTED(!ce->unserialize_func)) {
		ce->unserialize_func = parent->unserialize_func;
	}
	if (EXPECTED(!ce->unserialize)) {
		ce->unserialize = parent->unserialize;
	}
	if (!ce->destructor) {
		ce->destructor = parent->destructor;
	}
	if (EXPECTED(!ce->__debugInfo)) {
		ce->__debugInfo = parent->__debugInfo;
	}

	if (ce->constructor) {
		if (parent->constructor && UNEXPECTED(parent->constructor->common.fn_flags & ZEND_ACC_FINAL)) {
			zend_error_noreturn(E_ERROR, "Cannot override final %s::%s() with %s::%s()",
				ZSTR_VAL(parent->name), ZSTR_VAL(parent->constructor->common.function_name),
				ZSTR_VAL(ce->name), ZSTR_VAL(ce->constructor->common.function_name));
		}
		return;
	}

	ce->constructor = parent->constructor;
}