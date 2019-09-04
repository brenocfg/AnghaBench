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
#define  IS_ARRAY 132 
#define  IS_FALSE 131 
#define  IS_NULL 130 
#define  IS_STRING 129 
#define  PARTIAL_ARRAY 128 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int ct_eval_add_array_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_assign_dim(zval *result, zval *value, zval *key) {
	switch (Z_TYPE_P(result)) {
		case IS_NULL:
		case IS_FALSE:
			array_init(result);
			/* break missing intentionally */
		case IS_ARRAY:
		case PARTIAL_ARRAY:
			return ct_eval_add_array_elem(result, value, key);
		case IS_STRING:
			// TODO Before enabling this case, make sure ARRAY_DIM result op is correct
#if 0
			zend_long index;
			zend_string *new_str, *value_str;
			if (!key || Z_TYPE_P(value) == IS_ARRAY
					|| zval_to_string_offset(&index, key) == FAILURE || index < 0) {
				return FAILURE;
			}

			if (index >= Z_STRLEN_P(result)) {
				new_str = zend_string_alloc(index + 1, 0);
				memcpy(ZSTR_VAL(new_str), Z_STRVAL_P(result), Z_STRLEN_P(result));
				memset(ZSTR_VAL(new_str) + Z_STRLEN_P(result), ' ', index - Z_STRLEN_P(result));
				ZSTR_VAL(new_str)[index + 1] = 0;
			} else {
				new_str = zend_string_init(Z_STRVAL_P(result), Z_STRLEN_P(result), 0);
			}

			value_str = zval_get_string(value);
			ZVAL_STR(result, new_str);
			Z_STRVAL_P(result)[index] = ZSTR_VAL(value_str)[0];
			zend_string_release_ex(value_str, 0);
#endif
			return FAILURE;
		default:
			return FAILURE;
	}
}