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
struct TYPE_4__ {scalar_t__ kind; int attr; } ;
typedef  TYPE_1__ zend_ffi_type ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  FFI_G (int /*<<< orphan*/ ) ; 
 int ZEND_FFI_ATTR_INCOMPLETE_ARRAY ; 
 scalar_t__ ZEND_FFI_TYPE_ARRAY ; 
 scalar_t__ ZEND_FFI_TYPE_FUNC ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  zend_ffi_throw_parser_error (char*,int /*<<< orphan*/ ) ; 
 int zend_ffi_validate_type (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zend_ffi_validate_array_element_type(zend_ffi_type *type) /* {{{ */
{
	if (type->kind == ZEND_FFI_TYPE_FUNC) {
		zend_ffi_throw_parser_error("array of functions is not allowed at line %d", FFI_G(line));
		return FAILURE;
	} else if (type->kind == ZEND_FFI_TYPE_ARRAY && (type->attr & ZEND_FFI_ATTR_INCOMPLETE_ARRAY)) {
		zend_ffi_throw_parser_error("only the leftmost array can be undimensioned at line %d", FFI_G(line));
		return FAILURE;
	}
	return zend_ffi_validate_type(type, 0, 1);
}