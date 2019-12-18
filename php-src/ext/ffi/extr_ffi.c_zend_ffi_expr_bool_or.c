#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ kind; int i64; } ;
typedef  TYPE_1__ zend_ffi_val ;

/* Variables and functions */
 scalar_t__ ZEND_FFI_VAL_ERROR ; 
 scalar_t__ ZEND_FFI_VAL_INT32 ; 
 int /*<<< orphan*/  zend_ffi_expr_bool (TYPE_1__*) ; 

void zend_ffi_expr_bool_or(zend_ffi_val *val, zend_ffi_val *op2) /* {{{ */
{
	zend_ffi_expr_bool(val);
	zend_ffi_expr_bool(op2);
	if (val->kind == ZEND_FFI_VAL_INT32 && op2->kind == ZEND_FFI_VAL_INT32) {
		val->i64 = val->i64 || op2->i64;
	} else {
		val->kind = ZEND_FFI_VAL_ERROR;
	}
}