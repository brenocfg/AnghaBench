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
typedef  int uint32_t ;

/* Variables and functions */
 int FAILURE ; 
#define  IS_ARRAY 133 
#define  IS_DOUBLE 132 
#define  IS_LONG 131 
#define  IS_NULL 130 
#define  IS_STRING 129 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int const Z_TYPE_P (int /*<<< orphan*/ *) ; 
#define  _IS_BOOL 128 
 int /*<<< orphan*/  convert_to_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_get_double (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_get_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_is_true (int /*<<< orphan*/ *) ; 

int zend_optimizer_eval_cast(zval *result, uint32_t type, zval *op1) /* {{{ */
{
	switch (type) {
		case IS_NULL:
			ZVAL_NULL(result);
			return SUCCESS;
		case _IS_BOOL:
			ZVAL_BOOL(result, zval_is_true(op1));
			return SUCCESS;
		case IS_LONG:
			ZVAL_LONG(result, zval_get_long(op1));
			return SUCCESS;
		case IS_DOUBLE:
			ZVAL_DOUBLE(result, zval_get_double(op1));
			return SUCCESS;
		case IS_STRING:
			/* Conversion from double to string takes into account run-time
			   'precision' setting and cannot be evaluated at compile-time */
			if (Z_TYPE_P(op1) != IS_ARRAY && Z_TYPE_P(op1) != IS_DOUBLE) {
				ZVAL_STR(result, zval_get_string(op1));
				return SUCCESS;
			}
			break;
		case IS_ARRAY:
			ZVAL_COPY(result, op1);
			convert_to_array(result);
			return SUCCESS;
	}
	return FAILURE;
}