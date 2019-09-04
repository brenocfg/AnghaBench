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
typedef  int /*<<< orphan*/  zend_constant ;

/* Variables and functions */
 int ZEND_CONSTANT_MODULE_NUMBER (int /*<<< orphan*/ *) ; 
 int ZEND_HASH_APPLY_KEEP ; 
 int ZEND_HASH_APPLY_REMOVE ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clean_module_constant(zval *el, void *arg)
{
	zend_constant *c = (zend_constant *)Z_PTR_P(el);
	int module_number = *(int *)arg;

	if (ZEND_CONSTANT_MODULE_NUMBER(c) == module_number) {
		return ZEND_HASH_APPLY_REMOVE;
	} else {
		return ZEND_HASH_APPLY_KEEP;
	}
}