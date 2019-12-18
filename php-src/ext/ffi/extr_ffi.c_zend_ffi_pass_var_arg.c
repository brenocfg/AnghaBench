#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_long ;
typedef  int /*<<< orphan*/  zend_ffi_type ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_ffi_cdata ;
typedef  int /*<<< orphan*/  zend_execute_data ;
typedef  int uint8_t ;
typedef  size_t uint32_t ;
typedef  void* int64_t ;
typedef  void* int32_t ;
typedef  int /*<<< orphan*/  ffi_type ;

/* Variables and functions */
 int FAILURE ; 
#define  IS_DOUBLE 134 
#define  IS_FALSE 133 
#define  IS_LONG 132 
#define  IS_NULL 131 
#define  IS_OBJECT 130 
#define  IS_STRING 129 
#define  IS_TRUE 128 
 int SUCCESS ; 
 int /*<<< orphan*/ * ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 double Z_DVAL_P (int /*<<< orphan*/ *) ; 
 void* Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_OBJ_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffi_type_double ; 
 int /*<<< orphan*/  ffi_type_pointer ; 
 int /*<<< orphan*/  ffi_type_sint32 ; 
 int /*<<< orphan*/  ffi_type_sint64 ; 
 int /*<<< orphan*/  ffi_type_uint8 ; 
 int /*<<< orphan*/  zend_ffi_cdata_ce ; 
 int /*<<< orphan*/  zend_ffi_exception_ce ; 
 int zend_ffi_pass_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,void**,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int zend_ffi_pass_var_arg(zval *arg, ffi_type **pass_type, void **arg_values, uint32_t n, zend_execute_data *execute_data) /* {{{ */
{
	ZVAL_DEREF(arg);
	switch (Z_TYPE_P(arg)) {
		case IS_NULL:
			*pass_type = &ffi_type_pointer;
			*(void**)arg_values[n] = NULL;
			break;
		case IS_FALSE:
			*pass_type = &ffi_type_uint8;
			*(uint8_t*)arg_values[n] = 0;
			break;
		case IS_TRUE:
			*pass_type = &ffi_type_uint8;
			*(uint8_t*)arg_values[n] = 1;
			break;
		case IS_LONG:
			if (sizeof(zend_long) == 4) {
				*pass_type = &ffi_type_sint32;
				*(int32_t*)arg_values[n] = Z_LVAL_P(arg);
			} else {
				*pass_type = &ffi_type_sint64;
				*(int64_t*)arg_values[n] = Z_LVAL_P(arg);
			}
			break;
		case IS_DOUBLE:
			*pass_type = &ffi_type_double;
			*(double*)arg_values[n] = Z_DVAL_P(arg);
			break;
		case IS_STRING:
			*pass_type = &ffi_type_pointer;
			*(char**)arg_values[n] = Z_STRVAL_P(arg);
			break;
		case IS_OBJECT:
			if (Z_OBJCE_P(arg) == zend_ffi_cdata_ce) {
				zend_ffi_cdata *cdata = (zend_ffi_cdata*)Z_OBJ_P(arg);
				zend_ffi_type *type = ZEND_FFI_TYPE(cdata->type);

				return zend_ffi_pass_arg(arg, type, pass_type, arg_values, n, execute_data);
			}
			/* break missing intentionally */
		default:
			zend_throw_error(zend_ffi_exception_ce, "Unsupported argument type");
			return FAILURE;
	}
	return SUCCESS;
}