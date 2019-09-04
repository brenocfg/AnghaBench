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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  php_password_algo ;

/* Variables and functions */
 scalar_t__ IS_PTR ; 
 int /*<<< orphan*/  const* Z_PTR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_password_algos ; 
 int /*<<< orphan*/ * zend_hash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

const php_password_algo* php_password_algo_find(const zend_string *ident) {
	zval *tmp;

	if (!ident) {
		return NULL;
	}

	tmp = zend_hash_find(&php_password_algos, (zend_string*)ident);
	if (!tmp || (Z_TYPE_P(tmp) != IS_PTR)) {
		return NULL;
	}

	return Z_PTR_P(tmp);
}