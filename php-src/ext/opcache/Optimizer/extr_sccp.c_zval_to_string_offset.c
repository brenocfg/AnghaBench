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
typedef  int /*<<< orphan*/  zend_long ;

/* Variables and functions */
 int FAILURE ; 
#define  IS_LONG 129 
#define  IS_STRING 128 
 int SUCCESS ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int const is_numeric_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int zval_to_string_offset(zend_long *result, zval *op) {
	switch (Z_TYPE_P(op)) {
		case IS_LONG:
			*result = Z_LVAL_P(op);
			return SUCCESS;
		case IS_STRING:
			if (IS_LONG == is_numeric_string(
					Z_STRVAL_P(op), Z_STRLEN_P(op), result, NULL, 0)) {
				return SUCCESS;
			}
			return FAILURE;
		default:
			return FAILURE;
	}
}