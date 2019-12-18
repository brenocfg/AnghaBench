#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_4__ {scalar_t__ kind; } ;
typedef  TYPE_1__ zend_ffi_type ;
struct TYPE_5__ {scalar_t__ ptr; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ zend_ffi_cdata ;

/* Variables and functions */
 scalar_t__ IS_OBJECT ; 
 TYPE_1__* ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_FFI_TYPE_POINTER ; 
 scalar_t__ Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_OBJ_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_ffi_cdata_ce ; 
 int /*<<< orphan*/  zend_ffi_exception_ce ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int zend_ffi_cdata_compare_objects(zval *o1, zval *o2) /* {{{ */
{
	if (Z_TYPE_P(o1) == IS_OBJECT && Z_OBJCE_P(o1) == zend_ffi_cdata_ce &&
	    Z_TYPE_P(o2) == IS_OBJECT && Z_OBJCE_P(o2) == zend_ffi_cdata_ce) {
		zend_ffi_cdata *cdata1 = (zend_ffi_cdata*)Z_OBJ_P(o1);
		zend_ffi_cdata *cdata2 = (zend_ffi_cdata*)Z_OBJ_P(o2);
		zend_ffi_type *type1 = ZEND_FFI_TYPE(cdata1->type);
		zend_ffi_type *type2 = ZEND_FFI_TYPE(cdata2->type);

		if (type1->kind == ZEND_FFI_TYPE_POINTER && type2->kind == ZEND_FFI_TYPE_POINTER) {
			void *ptr1 = *(void**)cdata1->ptr;
			void *ptr2 = *(void**)cdata2->ptr;

			if (!ptr1 || !ptr2) {
				zend_throw_error(zend_ffi_exception_ce, "NULL pointer dereference");
				return 0;
			}
			return ptr1 == ptr2 ? 0 : (ptr1 < ptr2 ? -1 : 1);
		}
	}
	zend_throw_error(zend_ffi_exception_ce, "Comparison of incompatible C types");
	return 0;
}