#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_3__ {int /*<<< orphan*/ * __debugInfo; int /*<<< orphan*/ * __tostring; int /*<<< orphan*/ * __callstatic; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/ * __isset; int /*<<< orphan*/ * __unset; int /*<<< orphan*/ * __call; int /*<<< orphan*/ * __set; int /*<<< orphan*/ * __get; int /*<<< orphan*/ * destructor; int /*<<< orphan*/ * constructor; int /*<<< orphan*/ * clone; int /*<<< orphan*/ * unserialize_func; int /*<<< orphan*/ * serialize_func; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ACC_USE_GUARDS ; 
 char* ZEND_CALLSTATIC_FUNC_NAME ; 
 char* ZEND_CALL_FUNC_NAME ; 
 char* ZEND_CLONE_FUNC_NAME ; 
 char* ZEND_CONSTRUCTOR_FUNC_NAME ; 
 char* ZEND_DEBUGINFO_FUNC_NAME ; 
 char* ZEND_DESTRUCTOR_FUNC_NAME ; 
 char* ZEND_GET_FUNC_NAME ; 
 char* ZEND_ISSET_FUNC_NAME ; 
 char* ZEND_SET_FUNC_NAME ; 
 char* ZEND_TOSTRING_FUNC_NAME ; 
 char* ZEND_UNSET_FUNC_NAME ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_string_equals_literal (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void zend_add_magic_methods(zend_class_entry* ce, zend_string* mname, zend_function* fe) /* {{{ */
{
	if (zend_string_equals_literal(mname, "serialize")) {
		ce->serialize_func = fe;
	} else if (zend_string_equals_literal(mname, "unserialize")) {
		ce->unserialize_func = fe;
	} else if (ZSTR_VAL(mname)[0] != '_' || ZSTR_VAL(mname)[1] != '_') {
		/* pass */
	} else if (zend_string_equals_literal(mname, ZEND_CLONE_FUNC_NAME)) {
		ce->clone = fe;
	} else if (zend_string_equals_literal(mname, ZEND_CONSTRUCTOR_FUNC_NAME)) {
		ce->constructor = fe;
	} else if (zend_string_equals_literal(mname, ZEND_DESTRUCTOR_FUNC_NAME)) {
		ce->destructor = fe;
	} else if (zend_string_equals_literal(mname, ZEND_GET_FUNC_NAME)) {
		ce->__get = fe;
		ce->ce_flags |= ZEND_ACC_USE_GUARDS;
	} else if (zend_string_equals_literal(mname, ZEND_SET_FUNC_NAME)) {
		ce->__set = fe;
		ce->ce_flags |= ZEND_ACC_USE_GUARDS;
	} else if (zend_string_equals_literal(mname, ZEND_CALL_FUNC_NAME)) {
		ce->__call = fe;
	} else if (zend_string_equals_literal(mname, ZEND_UNSET_FUNC_NAME)) {
		ce->__unset = fe;
		ce->ce_flags |= ZEND_ACC_USE_GUARDS;
	} else if (zend_string_equals_literal(mname, ZEND_ISSET_FUNC_NAME)) {
		ce->__isset = fe;
		ce->ce_flags |= ZEND_ACC_USE_GUARDS;
	} else if (zend_string_equals_literal(mname, ZEND_CALLSTATIC_FUNC_NAME)) {
		ce->__callstatic = fe;
	} else if (zend_string_equals_literal(mname, ZEND_TOSTRING_FUNC_NAME)) {
		ce->__tostring = fe;
	} else if (zend_string_equals_literal(mname, ZEND_DEBUGINFO_FUNC_NAME)) {
		ce->__debugInfo = fe;
	}
}