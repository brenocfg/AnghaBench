#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  kind; int /*<<< orphan*/ * tag_name; } ;
struct TYPE_10__ {int attr; TYPE_1__ enumeration; int /*<<< orphan*/  align; int /*<<< orphan*/  size; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ zend_ffi_type ;
struct TYPE_11__ {int attr; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ zend_ffi_dcl ;
struct TYPE_13__ {int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;
struct TYPE_12__ {int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int FFI_G (int /*<<< orphan*/ ) ; 
 int ZEND_FFI_ATTR_PACKED ; 
 int ZEND_FFI_ENUM_ATTRS ; 
 int /*<<< orphan*/  ZEND_FFI_TYPE_ENUM ; 
 int /*<<< orphan*/  ZEND_FFI_TYPE_MAKE_OWNED (TYPE_2__*) ; 
 int /*<<< orphan*/  ZEND_FFI_TYPE_UINT32 ; 
 int /*<<< orphan*/  ZEND_FFI_TYPE_UINT8 ; 
 int /*<<< orphan*/  default_type_attr ; 
 TYPE_2__* pemalloc (int,int) ; 
 int /*<<< orphan*/  persistent ; 
 TYPE_5__ zend_ffi_type_uint32 ; 
 TYPE_4__ zend_ffi_type_uint8 ; 

void zend_ffi_make_enum_type(zend_ffi_dcl *dcl) /* {{{ */
{
	zend_ffi_type *type = pemalloc(sizeof(zend_ffi_type), FFI_G(persistent));
	type->kind = ZEND_FFI_TYPE_ENUM;
	type->attr = FFI_G(default_type_attr) | (dcl->attr & ZEND_FFI_ENUM_ATTRS);
	type->enumeration.tag_name = NULL;
	if (type->attr & ZEND_FFI_ATTR_PACKED) {
		type->size = zend_ffi_type_uint8.size;
		type->align = zend_ffi_type_uint8.align;
		type->enumeration.kind = ZEND_FFI_TYPE_UINT8;
	} else {
		type->size = zend_ffi_type_uint32.size;
		type->align = zend_ffi_type_uint32.align;
		type->enumeration.kind = ZEND_FFI_TYPE_UINT32;
	}
	dcl->type = ZEND_FFI_TYPE_MAKE_OWNED(type);
	dcl->attr &= ~ZEND_FFI_ENUM_ATTRS;
}