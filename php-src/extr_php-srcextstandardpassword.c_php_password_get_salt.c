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
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * php_password_make_salt (size_t) ; 
 scalar_t__ zend_hash_str_exists (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static zend_string* php_password_get_salt(zval *unused_, size_t required_salt_len, HashTable *options) {
	if (options && zend_hash_str_exists(options, "salt", sizeof("salt") - 1)) {
		php_error_docref(NULL, E_WARNING, "The 'salt' option is no longer supported. The provided salt has been been ignored");
	}

	return php_password_make_salt(required_salt_len);
}