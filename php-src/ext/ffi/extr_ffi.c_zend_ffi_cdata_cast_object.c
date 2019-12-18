#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int zend_ffi_type_kind ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int kind; } ;
struct TYPE_8__ {int kind; int attr; TYPE_2__ pointer; TYPE_1__ enumeration; } ;
typedef  TYPE_3__ zend_ffi_type ;
struct TYPE_9__ {void* ptr; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ zend_ffi_cdata ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int FAILURE ; 
 int IS_STRING ; 
 int SUCCESS ; 
 int ZEND_FFI_ATTR_CONST ; 
 TYPE_3__* ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
#define  ZEND_FFI_TYPE_BOOL 142 
#define  ZEND_FFI_TYPE_CHAR 141 
#define  ZEND_FFI_TYPE_DOUBLE 140 
#define  ZEND_FFI_TYPE_ENUM 139 
#define  ZEND_FFI_TYPE_FLOAT 138 
#define  ZEND_FFI_TYPE_LONGDOUBLE 137 
#define  ZEND_FFI_TYPE_POINTER 136 
#define  ZEND_FFI_TYPE_SINT16 135 
#define  ZEND_FFI_TYPE_SINT32 134 
#define  ZEND_FFI_TYPE_SINT64 133 
#define  ZEND_FFI_TYPE_SINT8 132 
#define  ZEND_FFI_TYPE_UINT16 131 
#define  ZEND_FFI_TYPE_UINT32 130 
#define  ZEND_FFI_TYPE_UINT64 129 
#define  ZEND_FFI_TYPE_UINT8 128 
 int /*<<< orphan*/  ZSTR_CHAR (unsigned char) ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,long double) ; 
 int /*<<< orphan*/  ZVAL_INTERNED_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  convert_to_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zend_ffi_cdata_cast_object(zend_object *readobj, zval *writeobj, int type) /* {{{ */
{
	if (type == IS_STRING) {
		zend_ffi_cdata *cdata = (zend_ffi_cdata*)readobj;
		zend_ffi_type  *ctype = ZEND_FFI_TYPE(cdata->type);
		void           *ptr = cdata->ptr;
		zend_ffi_type_kind kind = ctype->kind;

again:
	    switch (kind) {
			case ZEND_FFI_TYPE_FLOAT:
				ZVAL_DOUBLE(writeobj, *(float*)ptr);
				break;
			case ZEND_FFI_TYPE_DOUBLE:
				ZVAL_DOUBLE(writeobj, *(double*)ptr);
				break;
#ifdef HAVE_LONG_DOUBLE
			case ZEND_FFI_TYPE_LONGDOUBLE:
				ZVAL_DOUBLE(writeobj, *(long double*)ptr);
				break;
#endif
			case ZEND_FFI_TYPE_UINT8:
				ZVAL_LONG(writeobj, *(uint8_t*)ptr);
				break;
			case ZEND_FFI_TYPE_SINT8:
				ZVAL_LONG(writeobj, *(int8_t*)ptr);
				break;
			case ZEND_FFI_TYPE_UINT16:
				ZVAL_LONG(writeobj, *(uint16_t*)ptr);
				break;
			case ZEND_FFI_TYPE_SINT16:
				ZVAL_LONG(writeobj, *(int16_t*)ptr);
				break;
			case ZEND_FFI_TYPE_UINT32:
				ZVAL_LONG(writeobj, *(uint32_t*)ptr);
				break;
			case ZEND_FFI_TYPE_SINT32:
				ZVAL_LONG(writeobj, *(int32_t*)ptr);
				break;
			case ZEND_FFI_TYPE_UINT64:
				ZVAL_LONG(writeobj, *(uint64_t*)ptr);
				break;
			case ZEND_FFI_TYPE_SINT64:
				ZVAL_LONG(writeobj, *(int64_t*)ptr);
				break;
			case ZEND_FFI_TYPE_BOOL:
				ZVAL_BOOL(writeobj, *(uint8_t*)ptr);
				break;
			case ZEND_FFI_TYPE_CHAR:
				ZVAL_INTERNED_STR(writeobj, ZSTR_CHAR(*(unsigned char*)ptr));
				return SUCCESS;
			case ZEND_FFI_TYPE_ENUM:
				kind = ctype->enumeration.kind;
				goto again;
			case ZEND_FFI_TYPE_POINTER:
				if (*(void**)ptr == NULL) {
					ZVAL_NULL(writeobj);
					break;
				} else if ((ctype->attr & ZEND_FFI_ATTR_CONST) && ZEND_FFI_TYPE(ctype->pointer.type)->kind == ZEND_FFI_TYPE_CHAR) {
					ZVAL_STRING(writeobj, *(char**)ptr);
					return SUCCESS;
				}
				return FAILURE;
			default:
				return FAILURE;
		}
		convert_to_string(writeobj);
		return SUCCESS;
	}

	return FAILURE;
}