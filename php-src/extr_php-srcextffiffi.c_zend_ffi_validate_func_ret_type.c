#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ kind; } ;
typedef  TYPE_1__ zend_ffi_type ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  FFI_G (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_FFI_TYPE_ARRAY ; 
 scalar_t__ ZEND_FFI_TYPE_FUNC ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  zend_ffi_throw_parser_error (char*,int /*<<< orphan*/ ) ; 
 int zend_ffi_validate_incomplete_type (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zend_ffi_validate_func_ret_type(zend_ffi_type *type) /* {{{ */
{
	if (type->kind == ZEND_FFI_TYPE_FUNC) {
		zend_ffi_throw_parser_error("function returning function is not allowed at line %d", FFI_G(line));
		return FAILURE;
	 } else if (type->kind == ZEND_FFI_TYPE_ARRAY) {
		zend_ffi_throw_parser_error("function returning array is not allowed at line %d", FFI_G(line));
		return FAILURE;
	}
	return zend_ffi_validate_incomplete_type(type, 1, 0);
}