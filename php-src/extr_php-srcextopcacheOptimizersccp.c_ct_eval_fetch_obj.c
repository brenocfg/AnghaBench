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
 int /*<<< orphan*/  IS_BOT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_PARTIAL_OBJECT (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fetch_obj_prop (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_fetch_obj(zval *result, zval *op1, zval *op2) {
	if (IS_PARTIAL_OBJECT(op1)) {
		zval *value;
		if (fetch_obj_prop(&value, op1, op2) == SUCCESS && value && !IS_BOT(value)) {
			ZVAL_COPY(result, value);
			return SUCCESS;
		}
	}
	return FAILURE;
}