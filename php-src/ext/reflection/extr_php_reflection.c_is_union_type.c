#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zend_type ;
typedef  int zend_bool ;
typedef  int uint32_t ;

/* Variables and functions */
 int MAY_BE_BOOL ; 
 scalar_t__ ZEND_TYPE_HAS_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_HAS_LIST (int /*<<< orphan*/ ) ; 
 int ZEND_TYPE_PURE_MASK_WITHOUT_NULL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_bool is_union_type(zend_type type) {
	if (ZEND_TYPE_HAS_LIST(type)) {
		return 1;
	}
	uint32_t type_mask_without_null = ZEND_TYPE_PURE_MASK_WITHOUT_NULL(type);
	if (ZEND_TYPE_HAS_CLASS(type)) {
		return type_mask_without_null != 0;
	}
	if (type_mask_without_null == MAY_BE_BOOL) {
		return 0;
	}
	/* Check that only one bit is set. */
	return (type_mask_without_null & (type_mask_without_null - 1)) != 0;
}