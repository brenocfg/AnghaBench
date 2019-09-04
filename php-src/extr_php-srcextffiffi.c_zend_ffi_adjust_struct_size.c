#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ kind; int align; int attr; int size; } ;
typedef  TYPE_1__ zend_ffi_type ;
struct TYPE_6__ {int align; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ zend_ffi_dcl ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int ZEND_FFI_ATTR_PACKED ; 
 TYPE_1__* ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_FFI_TYPE_STRUCT ; 

void zend_ffi_adjust_struct_size(zend_ffi_dcl *dcl) /* {{{ */
{
	zend_ffi_type *struct_type = ZEND_FFI_TYPE(dcl->type);

	ZEND_ASSERT(struct_type->kind == ZEND_FFI_TYPE_STRUCT);
	if (dcl->align > struct_type->align) {
		struct_type->align = dcl->align;
	}
	if (!(struct_type->attr & ZEND_FFI_ATTR_PACKED)) {
		struct_type->size = ((struct_type->size + (struct_type->align - 1)) / struct_type->align) * struct_type->align;
	}
	dcl->align = 0;
}