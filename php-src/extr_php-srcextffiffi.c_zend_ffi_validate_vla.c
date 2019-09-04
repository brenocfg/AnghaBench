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
struct TYPE_3__ {int attr; } ;
typedef  TYPE_1__ zend_ffi_type ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  FFI_G (int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int ZEND_FFI_ATTR_VLA ; 
 int /*<<< orphan*/  allow_vla ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  zend_ffi_throw_parser_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zend_ffi_validate_vla(zend_ffi_type *type) /* {{{ */
{
	if (!FFI_G(allow_vla) && (type->attr & ZEND_FFI_ATTR_VLA)) {
		zend_ffi_throw_parser_error("'[*]' not allowed in other than function prototype scope at line %d", FFI_G(line));
		return FAILURE;
	}
	return SUCCESS;
}