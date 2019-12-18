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
 scalar_t__ FAILURE ; 
 scalar_t__ IS_BOT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_PARTIAL_OBJECT (int /*<<< orphan*/ *) ; 
 int SUCCESS ; 
 int ZEND_ISEMPTY ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int) ; 
 int ct_eval_isset_isempty (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fetch_obj_prop (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_isset_obj(zval *result, uint32_t extended_value, zval *op1, zval *op2) {
	if (IS_PARTIAL_OBJECT(op1)) {
		zval *value;
		if (fetch_obj_prop(&value, op1, op2) == FAILURE) {
			return FAILURE;
		}
		if (!value || IS_BOT(value)) {
			return FAILURE;
		}
		return ct_eval_isset_isempty(result, extended_value, value);
	} else {
		ZVAL_BOOL(result, (extended_value & ZEND_ISEMPTY));
		return SUCCESS;
	}
}