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
typedef  int /*<<< orphan*/  php_conv_err_t ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_CONV_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  PHP_CONV_ERR_SUCCESS ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* pemalloc (int,int) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  zend_tmp_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_get_tmp_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static php_conv_err_t php_conv_get_string_prop_ex(const HashTable *ht, char **pretval, size_t *pretval_len, char *field_name, size_t field_name_len, int persistent)
{
	zval *tmpval;

	*pretval = NULL;
	*pretval_len = 0;

	if ((tmpval = zend_hash_str_find((HashTable *)ht, field_name, field_name_len-1)) != NULL) {
		zend_string *tmp;
		zend_string *str = zval_get_tmp_string(tmpval, &tmp);

		*pretval = pemalloc(ZSTR_LEN(str) + 1, persistent);
		*pretval_len = ZSTR_LEN(str);
		memcpy(*pretval, ZSTR_VAL(str), ZSTR_LEN(str) + 1);
		zend_tmp_string_release(tmp);
	} else {
		return PHP_CONV_ERR_NOT_FOUND;
	}
	return PHP_CONV_ERR_SUCCESS;
}