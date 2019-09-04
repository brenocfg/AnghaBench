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
 int /*<<< orphan*/  SEPARATE_ARRAY (int /*<<< orphan*/ *) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZSTR_EMPTY_ALLOC () ; 
 int /*<<< orphan*/  Z_ARR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL_P (int /*<<< orphan*/ *) ; 
 int Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TRY_ADDREF_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int zend_dval_to_lval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_index_update (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_next_index_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_symtable_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_add_array_elem(zval *result, zval *value, zval *key) {
	if (!key) {
		SEPARATE_ARRAY(result);
		if ((value = zend_hash_next_index_insert(Z_ARR_P(result), value))) {
			Z_TRY_ADDREF_P(value);
			return SUCCESS;
		}
		return FAILURE;
	}

	switch (Z_TYPE_P(key)) {
		case IS_NULL:
			SEPARATE_ARRAY(result);
			value = zend_hash_update(Z_ARR_P(result), ZSTR_EMPTY_ALLOC(), value);
			break;
		case IS_FALSE:
			SEPARATE_ARRAY(result);
			value = zend_hash_index_update(Z_ARR_P(result), 0, value);
			break;
		case IS_TRUE:
			SEPARATE_ARRAY(result);
			value = zend_hash_index_update(Z_ARR_P(result), 1, value);
			break;
		case IS_LONG:
			SEPARATE_ARRAY(result);
			value = zend_hash_index_update(Z_ARR_P(result), Z_LVAL_P(key), value);
			break;
		case IS_DOUBLE:
			SEPARATE_ARRAY(result);
			value = zend_hash_index_update(
				Z_ARR_P(result), zend_dval_to_lval(Z_DVAL_P(key)), value);
			break;
		case IS_STRING:
			SEPARATE_ARRAY(result);
			value = zend_symtable_update(Z_ARR_P(result), Z_STR_P(key), value);
			break;
		default:
			return FAILURE;
	}

	Z_TRY_ADDREF_P(value);
	return SUCCESS;
}