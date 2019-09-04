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
#define  IS_STRING 128 
 int SUCCESS ; 
 int /*<<< orphan*/  Z_ARR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TRY_ADDREF_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_symtable_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_add_obj_prop(zval *result, zval *value, zval *key) {
	switch (Z_TYPE_P(key)) {
		case IS_STRING:
			value = zend_symtable_update(Z_ARR_P(result), Z_STR_P(key), value);
			break;
		default:
			return FAILURE;
	}

	Z_TRY_ADDREF_P(value);
	return SUCCESS;
}