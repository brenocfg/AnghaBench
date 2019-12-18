#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_ffi_cdata ;

/* Variables and functions */
 int /*<<< orphan*/  zend_ffi_cdata_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_ffi_cdata_free_obj(zend_object *object) /* {{{ */
{
	zend_ffi_cdata *cdata = (zend_ffi_cdata*)object;

	zend_ffi_cdata_dtor(cdata);
}