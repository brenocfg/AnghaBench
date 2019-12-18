#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* kind; int /*<<< orphan*/  ch; int /*<<< orphan*/  u64; int /*<<< orphan*/  d; int /*<<< orphan*/  i64; } ;
typedef  TYPE_1__ zend_ffi_val ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ zend_ffi_dcl ;
struct TYPE_9__ {int kind; } ;

/* Variables and functions */
 TYPE_6__* ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
#define  ZEND_FFI_TYPE_BOOL 140 
#define  ZEND_FFI_TYPE_CHAR 139 
#define  ZEND_FFI_TYPE_DOUBLE 138 
#define  ZEND_FFI_TYPE_FLOAT 137 
#define  ZEND_FFI_TYPE_LONGDOUBLE 136 
#define  ZEND_FFI_TYPE_SINT16 135 
#define  ZEND_FFI_TYPE_SINT32 134 
#define  ZEND_FFI_TYPE_SINT64 133 
#define  ZEND_FFI_TYPE_SINT8 132 
#define  ZEND_FFI_TYPE_UINT16 131 
#define  ZEND_FFI_TYPE_UINT32 130 
#define  ZEND_FFI_TYPE_UINT64 129 
#define  ZEND_FFI_TYPE_UINT8 128 
 void* ZEND_FFI_VAL_CHAR ; 
 void* ZEND_FFI_VAL_DOUBLE ; 
 void* ZEND_FFI_VAL_ERROR ; 
 void* ZEND_FFI_VAL_FLOAT ; 
 void* ZEND_FFI_VAL_INT32 ; 
 void* ZEND_FFI_VAL_INT64 ; 
 void* ZEND_FFI_VAL_LONG_DOUBLE ; 
 void* ZEND_FFI_VAL_UINT32 ; 
 void* ZEND_FFI_VAL_UINT64 ; 
 int /*<<< orphan*/  zend_ffi_finalize_type (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_ffi_type_dtor (int /*<<< orphan*/ ) ; 

void zend_ffi_expr_cast(zend_ffi_val *val, zend_ffi_dcl *dcl) /* {{{ */
{
	zend_ffi_finalize_type(dcl);
	switch (ZEND_FFI_TYPE(dcl->type)->kind) {
		case ZEND_FFI_TYPE_FLOAT:
			if (val->kind == ZEND_FFI_VAL_UINT32 || val->kind == ZEND_FFI_VAL_UINT64) {
				val->kind = ZEND_FFI_VAL_FLOAT;
				val->d = val->u64;
			} else if (val->kind == ZEND_FFI_VAL_INT32 || val->kind == ZEND_FFI_VAL_INT64) {
				val->kind = ZEND_FFI_VAL_FLOAT;
				val->d = val->i64;
			} else if (val->kind == ZEND_FFI_VAL_FLOAT || val->kind == ZEND_FFI_VAL_DOUBLE || val->kind == ZEND_FFI_VAL_LONG_DOUBLE) {
				val->kind = ZEND_FFI_VAL_FLOAT;
			} else if (val->kind == ZEND_FFI_VAL_CHAR) {
				val->kind = ZEND_FFI_VAL_FLOAT;
				val->d = val->ch;
			} else {
				val->kind = ZEND_FFI_VAL_ERROR;
			}
			break;
		case ZEND_FFI_TYPE_DOUBLE:
			if (val->kind == ZEND_FFI_VAL_UINT32 || val->kind == ZEND_FFI_VAL_UINT64) {
				val->kind = ZEND_FFI_VAL_DOUBLE;
				val->d = val->u64;
			} else if (val->kind == ZEND_FFI_VAL_INT32 || val->kind == ZEND_FFI_VAL_INT64) {
				val->kind = ZEND_FFI_VAL_DOUBLE;
				val->d = val->i64;
			} else if (val->kind == ZEND_FFI_VAL_FLOAT || val->kind == ZEND_FFI_VAL_DOUBLE || val->kind == ZEND_FFI_VAL_LONG_DOUBLE) {
				val->kind = ZEND_FFI_VAL_DOUBLE;
			} else if (val->kind == ZEND_FFI_VAL_CHAR) {
				val->kind = ZEND_FFI_VAL_DOUBLE;
				val->d = val->ch;
			} else {
				val->kind = ZEND_FFI_VAL_ERROR;
			}
			break;
#ifdef HAVE_LONG_DOUBLE
		case ZEND_FFI_TYPE_LONGDOUBLE:
			if (val->kind == ZEND_FFI_VAL_UINT32 || val->kind == ZEND_FFI_VAL_UINT64) {
				val->kind = ZEND_FFI_VAL_LONG_DOUBLE;
				val->d = val->u64;
			} else if (val->kind == ZEND_FFI_VAL_INT32 || val->kind == ZEND_FFI_VAL_INT64) {
				val->kind = ZEND_FFI_VAL_LONG_DOUBLE;
				val->d = val->i64;
			} else if (val->kind == ZEND_FFI_VAL_FLOAT || val->kind == ZEND_FFI_VAL_DOUBLE || val->kind == ZEND_FFI_VAL_LONG_DOUBLE) {
				val->kind = ZEND_FFI_VAL_LONG_DOUBLE;
			} else if (val->kind == ZEND_FFI_VAL_CHAR) {
				val->kind = ZEND_FFI_VAL_LONG_DOUBLE;
				val->d = val->ch;
			} else {
				val->kind = ZEND_FFI_VAL_ERROR;
			}
			break;
#endif
		case ZEND_FFI_TYPE_UINT8:
		case ZEND_FFI_TYPE_UINT16:
		case ZEND_FFI_TYPE_UINT32:
		case ZEND_FFI_TYPE_BOOL:
			if (val->kind == ZEND_FFI_VAL_UINT32 || val->kind == ZEND_FFI_VAL_UINT64 || val->kind == ZEND_FFI_VAL_INT32 || val->kind == ZEND_FFI_VAL_INT64) {
				val->kind = ZEND_FFI_VAL_UINT32;
			} else if (val->kind == ZEND_FFI_VAL_FLOAT || val->kind == ZEND_FFI_VAL_DOUBLE || val->kind == ZEND_FFI_VAL_LONG_DOUBLE) {
				val->kind = ZEND_FFI_VAL_UINT32;
				val->u64 = val->d;
			} else if (val->kind == ZEND_FFI_VAL_CHAR) {
				val->kind = ZEND_FFI_VAL_UINT32;
				val->u64 = val->ch;
			} else {
				val->kind = ZEND_FFI_VAL_ERROR;
			}
			break;
		case ZEND_FFI_TYPE_SINT8:
		case ZEND_FFI_TYPE_SINT16:
		case ZEND_FFI_TYPE_SINT32:
			if (val->kind == ZEND_FFI_VAL_UINT32 || val->kind == ZEND_FFI_VAL_UINT64 || val->kind == ZEND_FFI_VAL_INT32 || val->kind == ZEND_FFI_VAL_INT64) {
				val->kind = ZEND_FFI_VAL_INT32;
			} else if (val->kind == ZEND_FFI_VAL_FLOAT || val->kind == ZEND_FFI_VAL_DOUBLE || val->kind == ZEND_FFI_VAL_LONG_DOUBLE) {
				val->kind = ZEND_FFI_VAL_INT32;
				val->i64 = val->d;
			} else if (val->kind == ZEND_FFI_VAL_CHAR) {
				val->kind = ZEND_FFI_VAL_INT32;
				val->i64 = val->ch;
			} else {
				val->kind = ZEND_FFI_VAL_ERROR;
			}
			break;
		case ZEND_FFI_TYPE_UINT64:
			if (val->kind == ZEND_FFI_VAL_UINT32 || val->kind == ZEND_FFI_VAL_UINT64 || val->kind == ZEND_FFI_VAL_INT32 || val->kind == ZEND_FFI_VAL_INT64) {
				val->kind = ZEND_FFI_VAL_UINT64;
			} else if (val->kind == ZEND_FFI_VAL_FLOAT || val->kind == ZEND_FFI_VAL_DOUBLE || val->kind == ZEND_FFI_VAL_LONG_DOUBLE) {
				val->kind = ZEND_FFI_VAL_UINT64;
				val->u64 = val->d;
			} else if (val->kind == ZEND_FFI_VAL_CHAR) {
				val->kind = ZEND_FFI_VAL_UINT64;
				val->u64 = val->ch;
			} else {
				val->kind = ZEND_FFI_VAL_ERROR;
			}
			break;
		case ZEND_FFI_TYPE_SINT64:
			if (val->kind == ZEND_FFI_VAL_UINT32 || val->kind == ZEND_FFI_VAL_UINT64) {
				val->kind = ZEND_FFI_VAL_CHAR;
				val->ch = val->u64;
			} else if (val->kind == ZEND_FFI_VAL_INT32 || val->kind == ZEND_FFI_VAL_INT64) {
				val->kind = ZEND_FFI_VAL_CHAR;
				val->ch = val->i64;
			} else if (val->kind == ZEND_FFI_VAL_FLOAT || val->kind == ZEND_FFI_VAL_DOUBLE || val->kind == ZEND_FFI_VAL_LONG_DOUBLE) {
				val->kind = ZEND_FFI_VAL_CHAR;
				val->ch = val->d;
			} else if (val->kind == ZEND_FFI_VAL_CHAR) {
			} else {
				val->kind = ZEND_FFI_VAL_ERROR;
			}
			break;
		case ZEND_FFI_TYPE_CHAR:
			if (val->kind == ZEND_FFI_VAL_UINT32 || val->kind == ZEND_FFI_VAL_UINT64 || val->kind == ZEND_FFI_VAL_INT32 || val->kind == ZEND_FFI_VAL_INT64) {
				val->kind = ZEND_FFI_VAL_UINT32;
			} else if (val->kind == ZEND_FFI_VAL_FLOAT || val->kind == ZEND_FFI_VAL_DOUBLE || val->kind == ZEND_FFI_VAL_LONG_DOUBLE) {
				val->kind = ZEND_FFI_VAL_UINT32;
				val->u64 = val->d;
			} else if (val->kind == ZEND_FFI_VAL_CHAR) {
				val->kind = ZEND_FFI_VAL_UINT32;
				val->u64 = val->ch;
			} else {
				val->kind = ZEND_FFI_VAL_ERROR;
			}
			break;
		default:
			val->kind = ZEND_FFI_VAL_ERROR;
			break;
	}
	zend_ffi_type_dtor(dcl->type);
}