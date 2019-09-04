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
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_symtable_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int fetch_obj_prop(zval **result, zval *op1, zval *op2) {
	switch (Z_TYPE_P(op2)) {
		case IS_STRING:
			*result = zend_symtable_find(Z_ARR_P(op1), Z_STR_P(op2));
			return SUCCESS;
		default:
			return FAILURE;
	}
}