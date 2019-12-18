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
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_BOT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_STRING ; 
 int SUCCESS ; 
 int ZEND_ISEMPTY ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int ct_eval_isset_isempty (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fetch_array_elem (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_isset_dim(zval *result, uint32_t extended_value, zval *op1, zval *op2) {
	if (Z_TYPE_P(op1) == IS_ARRAY || IS_PARTIAL_ARRAY(op1)) {
		zval *value;
		if (fetch_array_elem(&value, op1, op2) == FAILURE) {
			return FAILURE;
		}
		if (IS_PARTIAL_ARRAY(op1) && (!value || IS_BOT(value))) {
			return FAILURE;
		}
		return ct_eval_isset_isempty(result, extended_value, value);
	} else if (Z_TYPE_P(op1) == IS_STRING) {
		// TODO
		return FAILURE;
	} else {
		ZVAL_BOOL(result, (extended_value & ZEND_ISEMPTY));
		return SUCCESS;
	}
}