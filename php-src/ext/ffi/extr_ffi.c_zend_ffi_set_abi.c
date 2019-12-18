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
struct TYPE_3__ {scalar_t__ abi; } ;
typedef  TYPE_1__ zend_ffi_dcl ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  FFI_G (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_FFI_ABI_DEFAULT ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  zend_ffi_parser_error (char*,int /*<<< orphan*/ ) ; 

void zend_ffi_set_abi(zend_ffi_dcl *dcl, uint16_t abi) /* {{{ */
{
	if (dcl->abi != ZEND_FFI_ABI_DEFAULT) {
		zend_ffi_parser_error("multiple calling convention specifiers at line %d", FFI_G(line));
	} else {
		dcl->abi = abi;
	}
}