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
#define  IS_DOUBLE 133 
#define  IS_FALSE 132 
#define  IS_LONG 131 
#define  IS_NULL 130 
#define  IS_STRING 129 
#define  IS_TRUE 128 
 int SUCCESS ; 
 int /*<<< orphan*/  ZSTR_EMPTY_ALLOC () ; 
 int /*<<< orphan*/  Z_ARR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL_P (int /*<<< orphan*/ *) ; 
 int Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int zend_dval_to_lval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_index_find (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * zend_symtable_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int fetch_array_elem(zval **result, zval *op1, zval *op2) {
	switch (Z_TYPE_P(op2)) {
		case IS_NULL:
			*result = zend_hash_find(Z_ARR_P(op1), ZSTR_EMPTY_ALLOC());
			return SUCCESS;
		case IS_FALSE:
			*result = zend_hash_index_find(Z_ARR_P(op1), 0);
			return SUCCESS;
		case IS_TRUE:
			*result = zend_hash_index_find(Z_ARR_P(op1), 1);
			return SUCCESS;
		case IS_LONG:
			*result = zend_hash_index_find(Z_ARR_P(op1), Z_LVAL_P(op2));
			return SUCCESS;
		case IS_DOUBLE:
			*result = zend_hash_index_find(Z_ARR_P(op1), zend_dval_to_lval(Z_DVAL_P(op2)));
			return SUCCESS;
		case IS_STRING:
			*result = zend_symtable_find(Z_ARR_P(op1), Z_STR_P(op2));
			return SUCCESS;
		default:
			return FAILURE;
	}
}