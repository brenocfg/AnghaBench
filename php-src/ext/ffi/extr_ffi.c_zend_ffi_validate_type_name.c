#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_ffi_dcl ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  FFI_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LONGJMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bailout ; 
 int /*<<< orphan*/  zend_ffi_cleanup_dcl (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ffi_finalize_type (TYPE_1__*) ; 
 scalar_t__ zend_ffi_validate_var_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zend_ffi_validate_type_name(zend_ffi_dcl *dcl) /* {{{ */
{
	zend_ffi_finalize_type(dcl);
	if (zend_ffi_validate_var_type(ZEND_FFI_TYPE(dcl->type), 0) != SUCCESS) {
		zend_ffi_cleanup_dcl(dcl);
		LONGJMP(FFI_G(bailout), FAILURE);
	}
}