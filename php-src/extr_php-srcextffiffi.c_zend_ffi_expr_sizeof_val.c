#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ kind; scalar_t__ len; scalar_t__ u64; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ zend_ffi_val ;
struct TYPE_15__ {scalar_t__ size; } ;
struct TYPE_14__ {scalar_t__ size; } ;
struct TYPE_13__ {scalar_t__ size; } ;
struct TYPE_12__ {scalar_t__ size; } ;
struct TYPE_11__ {scalar_t__ size; } ;
struct TYPE_10__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ ZEND_FFI_VAL_CHAR ; 
 scalar_t__ ZEND_FFI_VAL_DOUBLE ; 
 void* ZEND_FFI_VAL_ERROR ; 
 scalar_t__ ZEND_FFI_VAL_FLOAT ; 
 scalar_t__ ZEND_FFI_VAL_INT32 ; 
 scalar_t__ ZEND_FFI_VAL_INT64 ; 
 scalar_t__ ZEND_FFI_VAL_LONG_DOUBLE ; 
 scalar_t__ ZEND_FFI_VAL_STRING ; 
 scalar_t__ ZEND_FFI_VAL_UINT32 ; 
 scalar_t__ ZEND_FFI_VAL_UINT64 ; 
 scalar_t__ memchr (int /*<<< orphan*/ ,char,scalar_t__) ; 
 TYPE_7__ zend_ffi_type_char ; 
 TYPE_6__ zend_ffi_type_double ; 
 TYPE_5__ zend_ffi_type_float ; 
 TYPE_4__ zend_ffi_type_long_double ; 
 TYPE_3__ zend_ffi_type_uint32 ; 
 TYPE_2__ zend_ffi_type_uint64 ; 

void zend_ffi_expr_sizeof_val(zend_ffi_val *val) /* {{{ */
{
	if (val->kind == ZEND_FFI_VAL_UINT32 || val->kind == ZEND_FFI_VAL_INT32) {
		val->kind = ZEND_FFI_VAL_UINT32;
		val->u64 = zend_ffi_type_uint32.size;
	} else if (val->kind == ZEND_FFI_VAL_UINT64 || val->kind == ZEND_FFI_VAL_INT64) {
		val->kind = ZEND_FFI_VAL_UINT32;
		val->u64 = zend_ffi_type_uint64.size;
	} else if (val->kind == ZEND_FFI_VAL_FLOAT) {
		val->kind = ZEND_FFI_VAL_UINT32;
		val->u64 = zend_ffi_type_float.size;
	} else if (val->kind == ZEND_FFI_VAL_DOUBLE) {
		val->kind = ZEND_FFI_VAL_UINT32;
		val->u64 = zend_ffi_type_double.size;
	} else if (val->kind == ZEND_FFI_VAL_LONG_DOUBLE) {
		val->kind = ZEND_FFI_VAL_UINT32;
#ifdef _WIN32
		val->u64 = zend_ffi_type_double.size;
#else
		val->u64 = zend_ffi_type_long_double.size;
#endif
	} else if (val->kind == ZEND_FFI_VAL_CHAR) {
		val->kind = ZEND_FFI_VAL_UINT32;
		val->u64 = zend_ffi_type_char.size;
	} else if (val->kind == ZEND_FFI_VAL_STRING) {
		if (memchr(val->str, '\\', val->len)) {
			// TODO: support for escape sequences ???
			val->kind = ZEND_FFI_VAL_ERROR;
		} else {
			val->kind = ZEND_FFI_VAL_UINT32;
			val->u64 = val->len + 1;
		}
	} else {
		val->kind = ZEND_FFI_VAL_ERROR;
	}
}