#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_6__ {int fn_flags; int /*<<< orphan*/  function_name; TYPE_2__* scope; } ;
typedef  TYPE_1__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_7__ {int ce_flags; int /*<<< orphan*/ * __debugInfo; int /*<<< orphan*/ * __tostring; int /*<<< orphan*/ * __isset; int /*<<< orphan*/ * __unset; int /*<<< orphan*/ * __set; int /*<<< orphan*/ * __get; int /*<<< orphan*/ * __callstatic; int /*<<< orphan*/ * __call; int /*<<< orphan*/ * clone; int /*<<< orphan*/ * destructor; int /*<<< orphan*/ * constructor; int /*<<< orphan*/ * unserialize_func; int /*<<< orphan*/ * serialize_func; int /*<<< orphan*/ * name; int /*<<< orphan*/  function_table; } ;
typedef  TYPE_2__ zend_class_entry ;
typedef  int zend_bool ;
typedef  int uint32_t ;

/* Variables and functions */
 TYPE_2__* CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int ZEND_ACC_ABSTRACT ; 
 int ZEND_ACC_FINAL ; 
 int ZEND_ACC_IMPLICIT_ABSTRACT_CLASS ; 
 int ZEND_ACC_INTERFACE ; 
 int ZEND_ACC_PRIVATE ; 
 int ZEND_ACC_PUBLIC ; 
 int ZEND_ACC_USE_GUARDS ; 
 char* ZEND_CALLSTATIC_FUNC_NAME ; 
 char* ZEND_CALL_FUNC_NAME ; 
 char* ZEND_CLONE_FUNC_NAME ; 
 char* ZEND_CONSTRUCTOR_FUNC_NAME ; 
 char* ZEND_DEBUGINFO_FUNC_NAME ; 
 char* ZEND_DESTRUCTOR_FUNC_NAME ; 
 char* ZEND_GET_FUNC_NAME ; 
 char* ZEND_INVOKE_FUNC_NAME ; 
 char* ZEND_ISSET_FUNC_NAME ; 
 char* ZEND_SET_FUNC_NAME ; 
 char* ZEND_TOSTRING_FUNC_NAME ; 
 char* ZEND_UNSET_FUNC_NAME ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  active_class_entry ; 
 int /*<<< orphan*/  zend_check_magic_method_attr (int,char*,int) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int /*<<< orphan*/ * zend_hash_add_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * zend_new_interned_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_string_equals_literal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ *) ; 

void zend_begin_method_decl(zend_op_array *op_array, zend_string *name, zend_bool has_body) /* {{{ */
{
	zend_class_entry *ce = CG(active_class_entry);
	zend_bool in_interface = (ce->ce_flags & ZEND_ACC_INTERFACE) != 0;
	uint32_t fn_flags = op_array->fn_flags;

	zend_string *lcname;

	if (in_interface) {
		if (!(fn_flags & ZEND_ACC_PUBLIC) || (fn_flags & (ZEND_ACC_FINAL|ZEND_ACC_ABSTRACT))) {
			zend_error_noreturn(E_COMPILE_ERROR, "Access type for interface method "
				"%s::%s() must be omitted", ZSTR_VAL(ce->name), ZSTR_VAL(name));
		}
		op_array->fn_flags |= ZEND_ACC_ABSTRACT;
	}

	if (op_array->fn_flags & ZEND_ACC_ABSTRACT) {
		if (op_array->fn_flags & ZEND_ACC_PRIVATE) {
			zend_error_noreturn(E_COMPILE_ERROR, "%s function %s::%s() cannot be declared private",
				in_interface ? "Interface" : "Abstract", ZSTR_VAL(ce->name), ZSTR_VAL(name));
		}

		if (has_body) {
			zend_error_noreturn(E_COMPILE_ERROR, "%s function %s::%s() cannot contain body",
				in_interface ? "Interface" : "Abstract", ZSTR_VAL(ce->name), ZSTR_VAL(name));
		}

		ce->ce_flags |= ZEND_ACC_IMPLICIT_ABSTRACT_CLASS;
	} else if (!has_body) {
		zend_error_noreturn(E_COMPILE_ERROR, "Non-abstract method %s::%s() must contain body",
			ZSTR_VAL(ce->name), ZSTR_VAL(name));
	}

	op_array->scope = ce;
	op_array->function_name = zend_string_copy(name);

	lcname = zend_string_tolower(name);
	lcname = zend_new_interned_string(lcname);

	if (zend_hash_add_ptr(&ce->function_table, lcname, op_array) == NULL) {
		zend_error_noreturn(E_COMPILE_ERROR, "Cannot redeclare %s::%s()",
			ZSTR_VAL(ce->name), ZSTR_VAL(name));
	}

	if (zend_string_equals_literal(lcname, "serialize")) {
		ce->serialize_func = (zend_function *) op_array;
	} else if (zend_string_equals_literal(lcname, "unserialize")) {
		ce->unserialize_func = (zend_function *) op_array;
	} else if (ZSTR_VAL(lcname)[0] != '_' || ZSTR_VAL(lcname)[1] != '_') {
		/* pass */
	} else if (zend_string_equals_literal(lcname, ZEND_CONSTRUCTOR_FUNC_NAME)) {
		ce->constructor = (zend_function *) op_array;
	} else if (zend_string_equals_literal(lcname, ZEND_DESTRUCTOR_FUNC_NAME)) {
		ce->destructor = (zend_function *) op_array;
	} else if (zend_string_equals_literal(lcname, ZEND_CLONE_FUNC_NAME)) {
		ce->clone = (zend_function *) op_array;
	} else if (zend_string_equals_literal(lcname, ZEND_CALL_FUNC_NAME)) {
		zend_check_magic_method_attr(fn_flags, "__call", 0);
		ce->__call = (zend_function *) op_array;
	} else if (zend_string_equals_literal(lcname, ZEND_CALLSTATIC_FUNC_NAME)) {
		zend_check_magic_method_attr(fn_flags, "__callStatic", 1);
		ce->__callstatic = (zend_function *) op_array;
	} else if (zend_string_equals_literal(lcname, ZEND_GET_FUNC_NAME)) {
		zend_check_magic_method_attr(fn_flags, "__get", 0);
		ce->__get = (zend_function *) op_array;
		ce->ce_flags |= ZEND_ACC_USE_GUARDS;
	} else if (zend_string_equals_literal(lcname, ZEND_SET_FUNC_NAME)) {
		zend_check_magic_method_attr(fn_flags, "__set", 0);
		ce->__set = (zend_function *) op_array;
		ce->ce_flags |= ZEND_ACC_USE_GUARDS;
	} else if (zend_string_equals_literal(lcname, ZEND_UNSET_FUNC_NAME)) {
		zend_check_magic_method_attr(fn_flags, "__unset", 0);
		ce->__unset = (zend_function *) op_array;
		ce->ce_flags |= ZEND_ACC_USE_GUARDS;
	} else if (zend_string_equals_literal(lcname, ZEND_ISSET_FUNC_NAME)) {
		zend_check_magic_method_attr(fn_flags, "__isset", 0);
		ce->__isset = (zend_function *) op_array;
		ce->ce_flags |= ZEND_ACC_USE_GUARDS;
	} else if (zend_string_equals_literal(lcname, ZEND_TOSTRING_FUNC_NAME)) {
		zend_check_magic_method_attr(fn_flags, "__toString", 0);
		ce->__tostring = (zend_function *) op_array;
	} else if (zend_string_equals_literal(lcname, ZEND_INVOKE_FUNC_NAME)) {
		zend_check_magic_method_attr(fn_flags, "__invoke", 0);
	} else if (zend_string_equals_literal(lcname, ZEND_DEBUGINFO_FUNC_NAME)) {
		zend_check_magic_method_attr(fn_flags, "__debugInfo", 0);
		ce->__debugInfo = (zend_function *) op_array;
	}

	zend_string_release_ex(lcname, 0);
}