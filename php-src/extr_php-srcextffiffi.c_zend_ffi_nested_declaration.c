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
struct TYPE_6__ {int /*<<< orphan*/ * type; } ;
typedef  TYPE_1__ zend_ffi_dcl ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  FFI_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LONGJMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  bailout ; 
 int /*<<< orphan*/  zend_ffi_cleanup_dcl (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ffi_finalize_type (TYPE_1__*) ; 
 scalar_t__ zend_ffi_nested_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ffi_type_char ; 

void zend_ffi_nested_declaration(zend_ffi_dcl *dcl, zend_ffi_dcl *nested_dcl) /* {{{ */
{
	/* "char" is used as a terminator of nested declaration */
	zend_ffi_finalize_type(dcl);
	if (!nested_dcl->type || nested_dcl->type == &zend_ffi_type_char) {
		nested_dcl->type = dcl->type;
	} else {
		if (zend_ffi_nested_type(dcl->type, nested_dcl->type) != SUCCESS) {
			zend_ffi_cleanup_dcl(nested_dcl);
			LONGJMP(FFI_G(bailout), FAILURE);
		}
	}
	dcl->type = nested_dcl->type;
}