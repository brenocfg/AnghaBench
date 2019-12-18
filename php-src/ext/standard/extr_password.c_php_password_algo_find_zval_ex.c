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
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ IS_STRING ; 
 int Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_STR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const php_password_algo_argon2i ; 
 int /*<<< orphan*/  const php_password_algo_argon2id ; 
 int /*<<< orphan*/  const php_password_algo_bcrypt ; 
 int /*<<< orphan*/  const* php_password_algo_find (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const php_password_algo* php_password_algo_find_zval_ex(zval *arg, const php_password_algo* default_algo) {
	if (!arg || (Z_TYPE_P(arg) == IS_NULL)) {
		return default_algo;
	}

	if (Z_TYPE_P(arg) == IS_LONG) {
		switch (Z_LVAL_P(arg)) {
			case 0: return default_algo;
			case 1: return &php_password_algo_bcrypt;
#if HAVE_ARGON2LIB
			case 2: return &php_password_algo_argon2i;
			case 3: return &php_password_algo_argon2id;
#else
			case 2:
				{
				zend_string *n = zend_string_init("argon2i", sizeof("argon2i")-1, 0);
				const php_password_algo* ret = php_password_algo_find(n);
				zend_string_release(n);
				return ret;
				}
			case 3:
				{
				zend_string *n = zend_string_init("argon2id", sizeof("argon2id")-1, 0);
				const php_password_algo* ret = php_password_algo_find(n);
				zend_string_release(n);
				return ret;
				}
#endif
		}
		return NULL;
	}

	if (Z_TYPE_P(arg) != IS_STRING) {
		return NULL;
	}

	return php_password_algo_find(Z_STR_P(arg));
}