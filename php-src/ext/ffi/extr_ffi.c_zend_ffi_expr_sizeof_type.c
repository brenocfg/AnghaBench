#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int u64; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ zend_ffi_val ;
struct TYPE_9__ {int size; } ;
typedef  TYPE_2__ zend_ffi_type ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ zend_ffi_dcl ;

/* Variables and functions */
 TYPE_2__* ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_UINT32 ; 
 int /*<<< orphan*/  ZEND_FFI_VAL_UINT64 ; 
 int /*<<< orphan*/  zend_ffi_finalize_type (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_ffi_type_dtor (int /*<<< orphan*/ ) ; 

void zend_ffi_expr_sizeof_type(zend_ffi_val *val, zend_ffi_dcl *dcl) /* {{{ */
{
	zend_ffi_type *type;

	zend_ffi_finalize_type(dcl);
	type = ZEND_FFI_TYPE(dcl->type);
	val->kind = (type->size > 0xffffffff) ? ZEND_FFI_VAL_UINT64 : ZEND_FFI_VAL_UINT32;
	val->u64 = type->size;
	zend_ffi_type_dtor(dcl->type);
}