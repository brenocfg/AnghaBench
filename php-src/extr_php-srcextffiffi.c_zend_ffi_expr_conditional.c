#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ kind; scalar_t__ i64; } ;
typedef  TYPE_1__ zend_ffi_val ;

/* Variables and functions */
 scalar_t__ ZEND_FFI_VAL_INT32 ; 
 int /*<<< orphan*/  zend_ffi_expr_bool (TYPE_1__*) ; 

void zend_ffi_expr_conditional(zend_ffi_val *val, zend_ffi_val *op2, zend_ffi_val *op3) /* {{{ */
{
	zend_ffi_expr_bool(val);
	if (val->kind == ZEND_FFI_VAL_INT32) {
		if (val->i64) {
			*val = *op2;
		} else {
			*val = *op3;
		}
	}
}