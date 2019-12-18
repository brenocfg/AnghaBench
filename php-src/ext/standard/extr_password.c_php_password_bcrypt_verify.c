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
typedef  int /*<<< orphan*/  const zend_string ;
typedef  int zend_bool ;

/* Variables and functions */
 size_t ZSTR_LEN (int /*<<< orphan*/  const*) ; 
 int* ZSTR_VAL (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* php_crypt (int*,int,int*,int,int) ; 
 int /*<<< orphan*/  zend_string_free (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static zend_bool php_password_bcrypt_verify(const zend_string *password, const zend_string *hash) {
	size_t i;
	int status = 0;
	zend_string *ret = php_crypt(ZSTR_VAL(password), (int)ZSTR_LEN(password), ZSTR_VAL(hash), (int)ZSTR_LEN(hash), 1);

	if (!ret) {
		return 0;
	}

	if (ZSTR_LEN(ret) != ZSTR_LEN(hash) || ZSTR_LEN(hash) < 13) {
		zend_string_free(ret);
		return 0;
	}

	/* We're using this method instead of == in order to provide
	 * resistance towards timing attacks. This is a constant time
	 * equality check that will always check every byte of both
	 * values. */
	for (i = 0; i < ZSTR_LEN(hash); i++) {
		status |= (ZSTR_VAL(ret)[i] ^ ZSTR_VAL(hash)[i]);
	}

	zend_string_free(ret);
	return status == 0;
}