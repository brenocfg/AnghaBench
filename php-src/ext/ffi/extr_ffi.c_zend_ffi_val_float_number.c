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
struct TYPE_3__ {int /*<<< orphan*/  kind; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ zend_ffi_val ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_FFI_VAL_DOUBLE ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_FLOAT ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_LONG_DOUBLE ; 
 int /*<<< orphan*/  strtold (char const*,int /*<<< orphan*/ *) ; 

void zend_ffi_val_float_number(zend_ffi_val *val, const char *str, size_t str_len) /* {{{ */
{
	val->d = strtold(str, NULL);
	if (str[str_len-1] == 'f' || str[str_len-1] == 'F') {
		val->kind = ZEND_FFI_VAL_FLOAT;
	} else if (str[str_len-1] == 'l' || str[str_len-1] == 'L') {
		val->kind = ZEND_FFI_VAL_LONG_DOUBLE;
	} else {
		val->kind = ZEND_FFI_VAL_DOUBLE;
	}
}