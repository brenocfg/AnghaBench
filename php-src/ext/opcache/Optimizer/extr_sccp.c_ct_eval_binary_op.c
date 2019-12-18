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
typedef  int /*<<< orphan*/  zend_uchar ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
 int zend_optimizer_eval_binary_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_binary_op(zval *result, zend_uchar binop, zval *op1, zval *op2) {
	/* TODO: We could implement support for evaluation of + on partial arrays. */
	if (IS_PARTIAL_ARRAY(op1) || IS_PARTIAL_ARRAY(op2)) {
		return FAILURE;
	}

	return zend_optimizer_eval_binary_op(result, binop, op1, op2);
}