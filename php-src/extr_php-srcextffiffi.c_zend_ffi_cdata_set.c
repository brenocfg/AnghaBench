#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_ffi_type ;
struct TYPE_2__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_ffi_cdata ;

/* Variables and functions */
 int /*<<< orphan*/ * ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_ffi_zval_to_cdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_ffi_cdata_set(zend_object *obj, zval *value) /* {{{ */
{
	zend_ffi_cdata *cdata = (zend_ffi_cdata*)obj;
	zend_ffi_type  *type = ZEND_FFI_TYPE(cdata->type);

#if 0
	if (UNEXPECTED(!cdata->ptr)) {
		zend_throw_error(zend_ffi_exception_ce, "NULL pointer dereference");
		return;
	}
#endif

	zend_ffi_zval_to_cdata(cdata->ptr, type, value);
}