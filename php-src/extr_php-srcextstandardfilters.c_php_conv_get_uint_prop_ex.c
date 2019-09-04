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
typedef  scalar_t__ zend_ulong ;
typedef  int php_conv_err_t ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int PHP_CONV_ERR_SUCCESS ; 
 int php_conv_get_ulong_prop_ex (int /*<<< orphan*/  const*,scalar_t__*,char*,size_t) ; 

__attribute__((used)) static int php_conv_get_uint_prop_ex(const HashTable *ht, unsigned int *pretval, char *field_name, size_t field_name_len)
{
	zend_ulong l;
	php_conv_err_t err;

	*pretval = 0;

	if ((err = php_conv_get_ulong_prop_ex(ht, &l, field_name, field_name_len)) == PHP_CONV_ERR_SUCCESS) {
		*pretval = (unsigned int)l;
	}
	return err;
}