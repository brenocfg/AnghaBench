#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_arg_info ;
struct TYPE_4__ {int fn_flags; TYPE_1__* arg_info; int /*<<< orphan*/  function_name; } ;

/* Variables and functions */
 TYPE_2__* CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ IS_ITERABLE ; 
 int ZEND_ACC_GENERATOR ; 
 int ZEND_ACC_HAS_RETURN_TYPE ; 
 scalar_t__ ZEND_TYPE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_TYPE_IS_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_TYPE_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  active_op_array ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  zend_get_type_by_const (scalar_t__) ; 
 int /*<<< orphan*/  zend_string_equals_literal_ci (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void zend_mark_function_as_generator() /* {{{ */
{
	if (!CG(active_op_array)->function_name) {
		zend_error_noreturn(E_COMPILE_ERROR,
			"The \"yield\" expression can only be used inside a function");
	}

	if (CG(active_op_array)->fn_flags & ZEND_ACC_HAS_RETURN_TYPE) {
		zend_arg_info return_info = CG(active_op_array)->arg_info[-1];

		if (ZEND_TYPE_CODE(return_info.type) != IS_ITERABLE) {
			const char *msg = "Generators may only declare a return type of Generator, Iterator, Traversable, or iterable, %s is not permitted";

			if (!ZEND_TYPE_IS_CLASS(return_info.type)) {
				zend_error_noreturn(E_COMPILE_ERROR, msg, zend_get_type_by_const(ZEND_TYPE_CODE(return_info.type)));
			}

			if (!zend_string_equals_literal_ci(ZEND_TYPE_NAME(return_info.type), "Traversable")
				&& !zend_string_equals_literal_ci(ZEND_TYPE_NAME(return_info.type), "Iterator")
				&& !zend_string_equals_literal_ci(ZEND_TYPE_NAME(return_info.type), "Generator")) {
				zend_error_noreturn(E_COMPILE_ERROR, msg, ZSTR_VAL(ZEND_TYPE_NAME(return_info.type)));
			}
		}
	}

	CG(active_op_array)->fn_flags |= ZEND_ACC_GENERATOR;
}