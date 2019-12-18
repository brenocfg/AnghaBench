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
typedef  int /*<<< orphan*/  zend_bool ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  FFI_G (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_FFI_TYPE_VOID ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  zend_ffi_throw_parser_error (char*,int /*<<< orphan*/ ) ; 
 int zend_ffi_validate_incomplete_type (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zend_ffi_validate_type(zend_ffi_type *type, zend_bool allow_incomplete_tag, zend_bool allow_incomplete_array) /* {{{ */
{
	if (type->kind == ZEND_FFI_TYPE_VOID) {
		zend_ffi_throw_parser_error("'void' type is not allowed at line %d", FFI_G(line));
		return FAILURE;
	}
	return zend_ffi_validate_incomplete_type(type, allow_incomplete_tag, allow_incomplete_array);
}