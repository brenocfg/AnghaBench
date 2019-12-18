#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* str; size_t len; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ zend_ffi_val ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_FFI_VAL_ERROR ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_STRING ; 

void zend_ffi_val_string(zend_ffi_val *val, const char *str, size_t str_len) /* {{{ */
{
	if (str[0] != '\"') {
		val->kind = ZEND_FFI_VAL_ERROR;
	} else {
		val->kind = ZEND_FFI_VAL_STRING;
		val->str = str + 1;
		val->len = str_len - 2;
	}
}