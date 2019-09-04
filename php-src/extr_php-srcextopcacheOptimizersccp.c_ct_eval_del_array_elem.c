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
 int /*<<< orphan*/  IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
#define  IS_STRING 129 
#define  IS_TRUE 128 
 int SUCCESS ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_EMPTY_ALLOC () ; 
 int /*<<< orphan*/  Z_ARR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL_P (int /*<<< orphan*/ *) ; 
 int Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int zend_dval_to_lval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_index_del (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_symtable_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ct_eval_del_array_elem(zval *result, zval *key) {
	ZEND_ASSERT(IS_PARTIAL_ARRAY(result));

	switch (Z_TYPE_P(key)) {
		case IS_NULL:
			zend_hash_del(Z_ARR_P(result), ZSTR_EMPTY_ALLOC());
			break;
		case IS_FALSE:
			zend_hash_index_del(Z_ARR_P(result), 0);
			break;
		case IS_TRUE:
			zend_hash_index_del(Z_ARR_P(result), 1);
			break;
		case IS_LONG:
			zend_hash_index_del(Z_ARR_P(result), Z_LVAL_P(key));
			break;
		case IS_DOUBLE:
			zend_hash_index_del(Z_ARR_P(result), zend_dval_to_lval(Z_DVAL_P(key)));
			break;
		case IS_STRING:
			zend_symtable_del(Z_ARR_P(result), Z_STR_P(key));
			break;
		default:
			return FAILURE;
	}

	return SUCCESS;
}