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
typedef  int /*<<< orphan*/  php_password_algo ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_PTR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_password_algos ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ zend_hash_str_add (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int php_password_algo_register(const char *ident, const php_password_algo *algo) {
	zval zalgo;
	ZVAL_PTR(&zalgo, (php_password_algo*)algo);
	if (zend_hash_str_add(&php_password_algos, ident, strlen(ident), &zalgo)) {
		return SUCCESS;
	}
	return FAILURE;
}