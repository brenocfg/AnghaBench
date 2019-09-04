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
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  php_socket ;
typedef  int /*<<< orphan*/  php_sockaddr_storage ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  php_set_inet46_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_tmp_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_get_tmp_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int php_get_address_from_array(const HashTable *ht, const char *key,
	php_socket *sock, php_sockaddr_storage *ss, socklen_t *ss_len)
{
	zval *val;
	zend_string *str, *tmp_str;

	if ((val = zend_hash_str_find(ht, key, strlen(key))) == NULL) {
		php_error_docref(NULL, E_WARNING, "no key \"%s\" passed in optval", key);
		return FAILURE;
	}
	str = zval_get_tmp_string(val, &tmp_str);
	if (!php_set_inet46_addr(ss, ss_len, ZSTR_VAL(str), sock)) {
		zend_tmp_string_release(tmp_str);
		return FAILURE;
	}
	zend_tmp_string_release(tmp_str);
	return SUCCESS;
}