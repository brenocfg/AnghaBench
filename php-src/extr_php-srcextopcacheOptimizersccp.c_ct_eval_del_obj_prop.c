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
 int /*<<< orphan*/  IS_PARTIAL_OBJECT (int /*<<< orphan*/ *) ; 
#define  IS_STRING 128 
 int SUCCESS ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_symtable_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ct_eval_del_obj_prop(zval *result, zval *key) {
	ZEND_ASSERT(IS_PARTIAL_OBJECT(result));

	switch (Z_TYPE_P(key)) {
		case IS_STRING:
			zend_symtable_del(Z_ARR_P(result), Z_STR_P(key));
			break;
		default:
			return FAILURE;
	}

	return SUCCESS;
}