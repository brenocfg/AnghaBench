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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 int SUCCESS ; 
 int ZEND_ISEMPTY ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_is_true (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_isset_isempty(zval *result, uint32_t extended_value, zval *op1) {
	if (!(extended_value & ZEND_ISEMPTY)) {
		ZVAL_BOOL(result, Z_TYPE_P(op1) != IS_NULL);
	} else {
		ZVAL_BOOL(result, !zend_is_true(op1));
	}
	return SUCCESS;
}