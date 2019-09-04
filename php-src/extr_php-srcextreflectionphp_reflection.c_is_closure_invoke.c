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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_class_entry ;
typedef  int zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_INVOKE_FUNC_NAME ; 
 int /*<<< orphan*/ * zend_ce_closure ; 
 scalar_t__ zend_string_equals_literal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zend_bool is_closure_invoke(zend_class_entry *ce, zend_string *lcname) {
	return ce == zend_ce_closure
		&& zend_string_equals_literal(lcname, ZEND_INVOKE_FUNC_NAME);
}