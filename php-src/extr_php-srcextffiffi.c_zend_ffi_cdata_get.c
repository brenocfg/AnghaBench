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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_ffi_type ;
struct TYPE_3__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_ffi_cdata ;

/* Variables and functions */
 int /*<<< orphan*/  BP_VAR_R ; 
 int /*<<< orphan*/ * ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_ffi_cdata_to_zval (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval* zend_ffi_cdata_get(zend_object *obj, zval *rv) /* {{{ */
{
	zend_ffi_cdata *cdata = (zend_ffi_cdata*)obj;
	zend_ffi_type  *type = ZEND_FFI_TYPE(cdata->type);

#if 0
	if (UNEXPECTED(!cdata->ptr)) {
		zend_throw_error(zend_ffi_exception_ce, "NULL pointer dereference");
		return &EG(uninitialized_zval);
	}
#endif

	zend_ffi_cdata_to_zval(cdata, cdata->ptr, type, BP_VAR_R, rv, 0, 0);
	return rv;
}