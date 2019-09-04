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
struct TYPE_3__ {int /*<<< orphan*/ * type; } ;
typedef  TYPE_1__ zend_ffi_dcl ;

/* Variables and functions */
 int /*<<< orphan*/  zend_ffi_type_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_ffi_cleanup_dcl(zend_ffi_dcl *dcl) /* {{{ */
{
	if (dcl) {
		zend_ffi_type_dtor(dcl->type);
		dcl->type = NULL;
	}
}