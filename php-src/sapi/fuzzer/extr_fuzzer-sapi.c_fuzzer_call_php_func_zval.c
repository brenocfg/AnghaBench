#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int /*<<< orphan*/  CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_user_function (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  function_table ; 
 int /*<<< orphan*/  php_var_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

void fuzzer_call_php_func_zval(const char *func_name, int nargs, zval *args) {
	zval retval, func;

	ZVAL_STRING(&func, func_name);
	ZVAL_UNDEF(&retval);
	call_user_function(CG(function_table), NULL, &func, &retval, nargs, args);

	// TODO: check result?
	/* to ensure retval is not broken */
	php_var_dump(&retval, 0);

	/* cleanup */
	zval_ptr_dtor(&retval);
	zval_ptr_dtor(&func);
}