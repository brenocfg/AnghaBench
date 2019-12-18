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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_type ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ ZEND_TYPE_INIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void append_type_mask(zval *return_value, uint32_t type_mask) {
	append_type(return_value, (zend_type) ZEND_TYPE_INIT_MASK(type_mask));
}