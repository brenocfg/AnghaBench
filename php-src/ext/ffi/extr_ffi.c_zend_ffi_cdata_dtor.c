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
struct TYPE_3__ {int flags; void* ptr; void* ptr_holder; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_ffi_cdata ;

/* Variables and functions */
 int ZEND_FFI_FLAG_OWNED ; 
 int ZEND_FFI_FLAG_PERSISTENT ; 
 int /*<<< orphan*/  pefree (void*,int) ; 
 int /*<<< orphan*/  zend_ffi_type_dtor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_ffi_cdata_dtor(zend_ffi_cdata *cdata) /* {{{ */
{
	zend_ffi_type_dtor(cdata->type);
	if (cdata->flags & ZEND_FFI_FLAG_OWNED) {
		if (cdata->ptr != (void*)&cdata->ptr_holder) {
			pefree(cdata->ptr, cdata->flags & ZEND_FFI_FLAG_PERSISTENT);
		} else {
			pefree(cdata->ptr_holder, cdata->flags & ZEND_FFI_FLAG_PERSISTENT);
		}
	}
}