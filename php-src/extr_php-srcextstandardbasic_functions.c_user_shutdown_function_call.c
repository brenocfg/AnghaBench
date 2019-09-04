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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_3__ {int /*<<< orphan*/ * arguments; scalar_t__ arg_count; } ;
typedef  TYPE_1__ php_shutdown_function_entry ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_get_callable_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_is_callable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int user_shutdown_function_call(zval *zv) /* {{{ */
{
    php_shutdown_function_entry *shutdown_function_entry = Z_PTR_P(zv);
	zval retval;

	if (!zend_is_callable(&shutdown_function_entry->arguments[0], 0, NULL)) {
		zend_string *function_name
			= zend_get_callable_name(&shutdown_function_entry->arguments[0]);
		php_error(E_WARNING, "(Registered shutdown functions) Unable to call %s() - function does not exist", ZSTR_VAL(function_name));
		zend_string_release_ex(function_name, 0);
		return 0;
	}

	if (call_user_function(NULL, NULL,
				&shutdown_function_entry->arguments[0],
				&retval,
				shutdown_function_entry->arg_count - 1,
				shutdown_function_entry->arguments + 1) == SUCCESS)
	{
		zval_ptr_dtor(&retval);
	}
	return 0;
}