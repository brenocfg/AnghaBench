#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_4__ {int calling; int /*<<< orphan*/ * arguments; scalar_t__ arg_count; } ;
typedef  TYPE_1__ user_tick_function_entry ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_OBJECT ; 
 scalar_t__ IS_STRING ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 TYPE_3__* Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * zend_hash_index_find (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_tick_function_call(user_tick_function_entry *tick_fe) /* {{{ */
{
	zval retval;
	zval *function = &tick_fe->arguments[0];

	/* Prevent reentrant calls to the same user ticks function */
	if (! tick_fe->calling) {
		tick_fe->calling = 1;

		if (call_user_function(NULL, NULL,
								function,
								&retval,
								tick_fe->arg_count - 1,
								tick_fe->arguments + 1
								) == SUCCESS) {
			zval_ptr_dtor(&retval);

		} else {
			zval *obj, *method;

			if (Z_TYPE_P(function) == IS_STRING) {
				php_error_docref(NULL, E_WARNING, "Unable to call %s() - function does not exist", Z_STRVAL_P(function));
			} else if (	Z_TYPE_P(function) == IS_ARRAY
						&& (obj = zend_hash_index_find(Z_ARRVAL_P(function), 0)) != NULL
						&& (method = zend_hash_index_find(Z_ARRVAL_P(function), 1)) != NULL
						&& Z_TYPE_P(obj) == IS_OBJECT
						&& Z_TYPE_P(method) == IS_STRING) {
				php_error_docref(NULL, E_WARNING, "Unable to call %s::%s() - function does not exist", ZSTR_VAL(Z_OBJCE_P(obj)->name), Z_STRVAL_P(method));
			} else {
				php_error_docref(NULL, E_WARNING, "Unable to call tick function");
			}
		}

		tick_fe->calling = 0;
	}
}