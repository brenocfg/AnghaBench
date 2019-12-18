#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ kind; int u64; int i64; int ch; } ;
typedef  TYPE_2__ zend_ffi_val ;
struct TYPE_13__ {int length; int /*<<< orphan*/  type; } ;
struct TYPE_15__ {int attr; int size; TYPE_1__ array; int /*<<< orphan*/  align; int /*<<< orphan*/  kind; } ;
typedef  TYPE_3__ zend_ffi_type ;
struct TYPE_16__ {int attr; scalar_t__ align; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ zend_ffi_dcl ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int FFI_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LONGJMP (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 
 int ZEND_FFI_ARRAY_ATTRS ; 
 int /*<<< orphan*/  ZEND_FFI_DCL_TYPE_QUALIFIERS ; 
 TYPE_3__* ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_FFI_TYPE_ARRAY ; 
 int /*<<< orphan*/  ZEND_FFI_TYPE_MAKE_OWNED (TYPE_3__*) ; 
 scalar_t__ ZEND_FFI_VAL_CHAR ; 
 scalar_t__ ZEND_FFI_VAL_EMPTY ; 
 scalar_t__ ZEND_FFI_VAL_INT32 ; 
 scalar_t__ ZEND_FFI_VAL_INT64 ; 
 scalar_t__ ZEND_FFI_VAL_UINT32 ; 
 scalar_t__ ZEND_FFI_VAL_UINT64 ; 
 int /*<<< orphan*/  bailout ; 
 int /*<<< orphan*/  default_type_attr ; 
 int /*<<< orphan*/  line ; 
 TYPE_3__* pemalloc (int,int) ; 
 int /*<<< orphan*/  persistent ; 
 int /*<<< orphan*/  zend_ffi_cleanup_dcl (TYPE_4__*) ; 
 int /*<<< orphan*/  zend_ffi_finalize_type (TYPE_4__*) ; 
 int /*<<< orphan*/  zend_ffi_parser_error (char*,int) ; 
 scalar_t__ zend_ffi_validate_array_element_type (TYPE_3__*) ; 

void zend_ffi_make_array_type(zend_ffi_dcl *dcl, zend_ffi_val *len) /* {{{ */
{
	int length = 0;
	zend_ffi_type *element_type;
	zend_ffi_type *type;

	zend_ffi_finalize_type(dcl);
	element_type = ZEND_FFI_TYPE(dcl->type);

	if (len->kind == ZEND_FFI_VAL_EMPTY) {
		length = 0;
	} else if (len->kind == ZEND_FFI_VAL_UINT32 || len->kind == ZEND_FFI_VAL_UINT64) {
		length = len->u64;
	} else if (len->kind == ZEND_FFI_VAL_INT32 || len->kind == ZEND_FFI_VAL_INT64) {
		length = len->i64;
	} else if (len->kind == ZEND_FFI_VAL_CHAR) {
		length = len->ch;
	} else {
		zend_ffi_cleanup_dcl(dcl);
		zend_ffi_parser_error("unsupported array index type at line %d", FFI_G(line));
		return;
	}
	if (length < 0) {
		zend_ffi_cleanup_dcl(dcl);
		zend_ffi_parser_error("negative array index at line %d", FFI_G(line));
		return;
	}

	if (zend_ffi_validate_array_element_type(element_type) != SUCCESS) {
		zend_ffi_cleanup_dcl(dcl);
		LONGJMP(FFI_G(bailout), FAILURE);
	}

	type = pemalloc(sizeof(zend_ffi_type), FFI_G(persistent));
	type->kind = ZEND_FFI_TYPE_ARRAY;
	type->attr = FFI_G(default_type_attr) | (dcl->attr & ZEND_FFI_ARRAY_ATTRS);
	type->size = length * element_type->size;
	type->align = element_type->align;
	type->array.type = dcl->type;
	type->array.length = length;
	dcl->type = ZEND_FFI_TYPE_MAKE_OWNED(type);
	dcl->flags &= ~ZEND_FFI_DCL_TYPE_QUALIFIERS;
	dcl->attr &= ~ZEND_FFI_ARRAY_ATTRS;
	dcl->align = 0;
}