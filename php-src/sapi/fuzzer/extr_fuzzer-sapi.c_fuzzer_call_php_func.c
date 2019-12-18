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
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuzzer_call_php_func_zval (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

void fuzzer_call_php_func(const char *func_name, int nargs, char **params) {
	zval args[nargs];
	int i;

	for(i=0;i<nargs;i++) {
		ZVAL_STRING(&args[i], params[i]);
	}

	fuzzer_call_php_func_zval(func_name, nargs, args);

	for(i=0;i<nargs;i++) {
		zval_ptr_dtor(&args[i]);
		ZVAL_UNDEF(&args[i]);
	}
}