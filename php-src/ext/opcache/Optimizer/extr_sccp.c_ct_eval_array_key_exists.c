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

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_BOT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_STRING ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int fetch_array_elem (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_array_key_exists(zval *result, zval *op1, zval *op2) {
	zval *value;

	if (Z_TYPE_P(op2) != IS_ARRAY && !IS_PARTIAL_ARRAY(op2)) {
		return FAILURE;
	}
	if (Z_TYPE_P(op1) != IS_STRING && Z_TYPE_P(op1) != IS_LONG && Z_TYPE_P(op1) != IS_NULL) {
		return FAILURE;
	}
	if (fetch_array_elem(&value, op2, op1) == FAILURE) {
		return FAILURE;
	}
	if (IS_PARTIAL_ARRAY(op2) && (!value || IS_BOT(value))) {
		return FAILURE;
	}

	ZVAL_BOOL(result, value != NULL);
	return SUCCESS;
}