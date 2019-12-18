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
 scalar_t__ IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_TRUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_is_true (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_bool_cast(zval *result, zval *op) {
	if (IS_PARTIAL_ARRAY(op)) {
		if (zend_hash_num_elements(Z_ARRVAL_P(op)) == 0) {
			/* An empty partial array may be non-empty at runtime, we don't know whether the
			 * result will be true or false. */
			return FAILURE;
		}

		ZVAL_TRUE(result);
		return SUCCESS;
	}

	ZVAL_BOOL(result, zend_is_true(op));
	return SUCCESS;
}