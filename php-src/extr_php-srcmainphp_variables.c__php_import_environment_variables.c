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
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  int /*<<< orphan*/  zend_uchar ;

/* Variables and functions */
 scalar_t__ ZEND_HANDLE_NUMERIC_STR (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_CHAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_EMPTY_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_INTERNED_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NEW_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 char** environ ; 
 int /*<<< orphan*/  php_register_variable_quick (char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  tsrm_env_lock () ; 
 int /*<<< orphan*/  tsrm_env_unlock () ; 
 int /*<<< orphan*/  valid_environment_name (char*,char*) ; 
 int /*<<< orphan*/  zend_hash_index_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_init (char*,size_t,int /*<<< orphan*/ ) ; 

void _php_import_environment_variables(zval *array_ptr)
{
	char **env, *p;
	size_t name_len, len;
	zval val;
	zend_ulong idx;

	tsrm_env_lock();

	for (env = environ; env != NULL && *env != NULL; env++) {
		p = strchr(*env, '=');
		if (!p
		 || p == *env
		 || !valid_environment_name(*env, p)) {
			/* malformed entry? */
			continue;
		}
		name_len = p - *env;
		p++;
		len = strlen(p);
		if (len == 0) {
			ZVAL_EMPTY_STRING(&val);
		} else if (len == 1) {
			ZVAL_INTERNED_STR(&val, ZSTR_CHAR((zend_uchar)*p));
		} else {
			ZVAL_NEW_STR(&val, zend_string_init(p, len, 0));
		}
		if (ZEND_HANDLE_NUMERIC_STR(*env, name_len, idx)) {
			zend_hash_index_update(Z_ARRVAL_P(array_ptr), idx, &val);
		} else {
			php_register_variable_quick(*env, name_len, &val, Z_ARRVAL_P(array_ptr));
		}
	}
	
	tsrm_env_unlock();
}