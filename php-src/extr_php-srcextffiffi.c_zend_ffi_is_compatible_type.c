#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ length; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {scalar_t__ kind; TYPE_2__ array; TYPE_1__ pointer; } ;
typedef  TYPE_3__ zend_ffi_type ;

/* Variables and functions */
 TYPE_3__* ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_FFI_TYPE_ARRAY ; 
 scalar_t__ ZEND_FFI_TYPE_POINTER ; 
 scalar_t__ ZEND_FFI_TYPE_VOID ; 

__attribute__((used)) static int zend_ffi_is_compatible_type(zend_ffi_type *dst_type, zend_ffi_type *src_type) /* {{{ */
{
	while (1) {
		if (dst_type == src_type) {
			return 1;
		} else if (dst_type->kind == src_type->kind) {
			if (dst_type->kind < ZEND_FFI_TYPE_POINTER) {
				return 1;
			} else if (dst_type->kind == ZEND_FFI_TYPE_POINTER) {
				dst_type = ZEND_FFI_TYPE(dst_type->pointer.type);
				src_type = ZEND_FFI_TYPE(src_type->pointer.type);
				if (dst_type->kind == ZEND_FFI_TYPE_VOID ||
				    src_type->kind == ZEND_FFI_TYPE_VOID) {
				    return 1;
				}
			} else if (dst_type->kind == ZEND_FFI_TYPE_ARRAY &&
			           (dst_type->array.length == src_type->array.length ||
			            dst_type->array.length == 0)) {
				dst_type = ZEND_FFI_TYPE(dst_type->array.type);
				src_type = ZEND_FFI_TYPE(src_type->array.type);
			} else {
				break;
			}
		} else if (dst_type->kind == ZEND_FFI_TYPE_POINTER &&
		           src_type->kind == ZEND_FFI_TYPE_ARRAY) {
			dst_type = ZEND_FFI_TYPE(dst_type->pointer.type);
			src_type = ZEND_FFI_TYPE(src_type->array.type);
			if (dst_type->kind == ZEND_FFI_TYPE_VOID) {
			    return 1;
			}
		} else {
			break;
		}
	}
	return 0;
}