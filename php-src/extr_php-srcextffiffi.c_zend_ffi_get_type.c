#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_ffi_type_kind ;
struct TYPE_5__ {int kind; } ;
struct TYPE_6__ {int kind; int attr; TYPE_1__ enumeration; } ;
typedef  TYPE_2__ zend_ffi_type ;
typedef  int /*<<< orphan*/  ffi_type ;

/* Variables and functions */
 int ZEND_FFI_ATTR_UNION ; 
#define  ZEND_FFI_TYPE_BOOL 144 
#define  ZEND_FFI_TYPE_CHAR 143 
#define  ZEND_FFI_TYPE_DOUBLE 142 
#define  ZEND_FFI_TYPE_ENUM 141 
#define  ZEND_FFI_TYPE_FLOAT 140 
#define  ZEND_FFI_TYPE_LONGDOUBLE 139 
#define  ZEND_FFI_TYPE_POINTER 138 
#define  ZEND_FFI_TYPE_SINT16 137 
#define  ZEND_FFI_TYPE_SINT32 136 
#define  ZEND_FFI_TYPE_SINT64 135 
#define  ZEND_FFI_TYPE_SINT8 134 
#define  ZEND_FFI_TYPE_STRUCT 133 
#define  ZEND_FFI_TYPE_UINT16 132 
#define  ZEND_FFI_TYPE_UINT32 131 
#define  ZEND_FFI_TYPE_UINT64 130 
#define  ZEND_FFI_TYPE_UINT8 129 
#define  ZEND_FFI_TYPE_VOID 128 
 int /*<<< orphan*/  ffi_type_double ; 
 int /*<<< orphan*/  ffi_type_float ; 
 int /*<<< orphan*/  ffi_type_longdouble ; 
 int /*<<< orphan*/  ffi_type_pointer ; 
 int /*<<< orphan*/  ffi_type_sint16 ; 
 int /*<<< orphan*/  ffi_type_sint32 ; 
 int /*<<< orphan*/  ffi_type_sint64 ; 
 int /*<<< orphan*/  ffi_type_sint8 ; 
 int /*<<< orphan*/  ffi_type_uint16 ; 
 int /*<<< orphan*/  ffi_type_uint32 ; 
 int /*<<< orphan*/  ffi_type_uint64 ; 
 int /*<<< orphan*/  ffi_type_uint8 ; 
 int /*<<< orphan*/  ffi_type_void ; 
 int /*<<< orphan*/ * zend_ffi_make_fake_struct_type (TYPE_2__*) ; 

__attribute__((used)) static ffi_type *zend_ffi_get_type(zend_ffi_type *type) /* {{{ */
{
	zend_ffi_type_kind kind = type->kind;

again:
    switch (kind) {
		case ZEND_FFI_TYPE_FLOAT:
			return &ffi_type_float;
		case ZEND_FFI_TYPE_DOUBLE:
			return &ffi_type_double;
#ifndef PHP_WIN32
		case ZEND_FFI_TYPE_LONGDOUBLE:
			return &ffi_type_longdouble;
#endif
		case ZEND_FFI_TYPE_UINT8:
			return &ffi_type_uint8;
		case ZEND_FFI_TYPE_SINT8:
			return &ffi_type_sint8;
		case ZEND_FFI_TYPE_UINT16:
			return &ffi_type_uint16;
		case ZEND_FFI_TYPE_SINT16:
			return &ffi_type_sint16;
		case ZEND_FFI_TYPE_UINT32:
			return &ffi_type_uint32;
		case ZEND_FFI_TYPE_SINT32:
			return &ffi_type_sint32;
		case ZEND_FFI_TYPE_UINT64:
			return &ffi_type_uint64;
		case ZEND_FFI_TYPE_SINT64:
			return &ffi_type_sint64;
		case ZEND_FFI_TYPE_POINTER:
			return &ffi_type_pointer;
		case ZEND_FFI_TYPE_VOID:
			return &ffi_type_void;
		case ZEND_FFI_TYPE_BOOL:
			return &ffi_type_uint8;
		case ZEND_FFI_TYPE_CHAR:
			return &ffi_type_sint8;
		case ZEND_FFI_TYPE_ENUM:
			kind = type->enumeration.kind;
			goto again;
		case ZEND_FFI_TYPE_STRUCT:
			if (!(type->attr & ZEND_FFI_ATTR_UNION)) {
				ffi_type *t = zend_ffi_make_fake_struct_type(type);
				return t;
			}
			break;
		default:
			break;
	}
	return NULL;
}