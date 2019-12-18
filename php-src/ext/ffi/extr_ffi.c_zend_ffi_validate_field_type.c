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
struct TYPE_6__ {int attr; } ;
typedef  TYPE_1__ zend_ffi_type ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  FFI_G (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 
 int ZEND_FFI_ATTR_INCOMPLETE_ARRAY ; 
 int ZEND_FFI_ATTR_UNION ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  zend_ffi_throw_parser_error (char*,int /*<<< orphan*/ ) ; 
 int zend_ffi_validate_prev_field_type (TYPE_1__*) ; 
 scalar_t__ zend_ffi_validate_var_type (TYPE_1__*,int) ; 

__attribute__((used)) static int zend_ffi_validate_field_type(zend_ffi_type *type, zend_ffi_type *struct_type) /* {{{ */
{
	if (type == struct_type) {
		zend_ffi_throw_parser_error("struct/union can't contain an instance of itself at line %d", FFI_G(line));
		return FAILURE;
	} else if (zend_ffi_validate_var_type(type, 1) != SUCCESS) {
		return FAILURE;
	} else if (struct_type->attr & ZEND_FFI_ATTR_UNION) {
		if (type->attr & ZEND_FFI_ATTR_INCOMPLETE_ARRAY) {
			zend_ffi_throw_parser_error("flexible array member in union at line %d", FFI_G(line));
			return FAILURE;
		}
	}
	return zend_ffi_validate_prev_field_type(struct_type);
}