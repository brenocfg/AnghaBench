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
struct TYPE_3__ {scalar_t__ kind; } ;
typedef  TYPE_1__ zend_ffi_val ;

/* Variables and functions */
 scalar_t__ ZEND_FFI_VAL_CHAR ; 
 scalar_t__ ZEND_FFI_VAL_DOUBLE ; 
 scalar_t__ ZEND_FFI_VAL_ERROR ; 
 scalar_t__ ZEND_FFI_VAL_FLOAT ; 
 scalar_t__ ZEND_FFI_VAL_INT32 ; 
 scalar_t__ ZEND_FFI_VAL_INT64 ; 
 scalar_t__ ZEND_FFI_VAL_LONG_DOUBLE ; 
 scalar_t__ ZEND_FFI_VAL_UINT32 ; 
 scalar_t__ ZEND_FFI_VAL_UINT64 ; 

void zend_ffi_expr_plus(zend_ffi_val *val) /* {{{ */
{
	if (val->kind == ZEND_FFI_VAL_UINT32 || val->kind == ZEND_FFI_VAL_UINT64) {
	} else if (val->kind == ZEND_FFI_VAL_INT32 || val->kind == ZEND_FFI_VAL_INT64) {
	} else if (val->kind == ZEND_FFI_VAL_FLOAT || val->kind == ZEND_FFI_VAL_DOUBLE || val->kind == ZEND_FFI_VAL_LONG_DOUBLE) {
	} else if (val->kind == ZEND_FFI_VAL_CHAR) {
	} else {
		val->kind = ZEND_FFI_VAL_ERROR;
	}
}