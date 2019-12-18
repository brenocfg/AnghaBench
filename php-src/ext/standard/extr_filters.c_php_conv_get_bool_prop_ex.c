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
typedef  int /*<<< orphan*/  php_conv_err_t ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_CONV_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  PHP_CONV_ERR_SUCCESS ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ *,char*,size_t) ; 
 int zend_is_true (int /*<<< orphan*/ *) ; 

__attribute__((used)) static php_conv_err_t php_conv_get_bool_prop_ex(const HashTable *ht, int *pretval, char *field_name, size_t field_name_len)
{
	zval *tmpval = zend_hash_str_find((HashTable *)ht, field_name, field_name_len-1);
	if (tmpval != NULL) {
		*pretval = zend_is_true(tmpval);
		return PHP_CONV_ERR_SUCCESS;
	} else {
		*pretval = 0;
		return PHP_CONV_ERR_NOT_FOUND;
	}
}