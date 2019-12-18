#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ kind; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_ffi_tag ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_FFI_TYPE (int /*<<< orphan*/ ) ; 
 int zend_ffi_same_types (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zend_ffi_same_tags(zend_ffi_tag *old, zend_ffi_tag *tag) /* {{{ */
{
	if (old->kind != tag->kind) {
		return 0;
	}

	return zend_ffi_same_types(ZEND_FFI_TYPE(old->type), ZEND_FFI_TYPE(tag->type));
}