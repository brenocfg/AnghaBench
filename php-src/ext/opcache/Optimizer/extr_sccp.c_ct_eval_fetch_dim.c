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
typedef  size_t zend_long ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  IS_BOT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_STRING ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ fetch_array_elem (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ zval_to_string_offset (size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ct_eval_fetch_dim(zval *result, zval *op1, zval *op2, int support_strings) {
	if (Z_TYPE_P(op1) == IS_ARRAY || IS_PARTIAL_ARRAY(op1)) {
		zval *value;
		if (fetch_array_elem(&value, op1, op2) == SUCCESS && value && !IS_BOT(value)) {
			ZVAL_COPY(result, value);
			return SUCCESS;
		}
	} else if (support_strings && Z_TYPE_P(op1) == IS_STRING) {
		zend_long index;
		if (zval_to_string_offset(&index, op2) == FAILURE) {
			return FAILURE;
		}
		if (index >= 0 && index < Z_STRLEN_P(op1)) {
			ZVAL_STR(result, zend_string_init(&Z_STRVAL_P(op1)[index], 1, 0));
			return SUCCESS;
		}
	}
	return FAILURE;
}