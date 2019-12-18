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
typedef  scalar_t__ zend_long ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int FAILURE ; 
#define  IS_DOUBLE 129 
#define  IS_LONG 128 
 scalar_t__ IS_STRING ; 
 int SUCCESS ; 
 scalar_t__ Z_DVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int is_numeric_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,double*,int) ; 

__attribute__((used)) static int zval_get_i64(zval *zv, int64_t *retval) {
    if (Z_TYPE_P(zv) == IS_LONG) {
        *retval = (int64_t)Z_LVAL_P(zv);
        return SUCCESS;
    } else if (Z_TYPE_P(zv) == IS_DOUBLE) {
        *retval = (int64_t)Z_DVAL_P(zv);
        return SUCCESS;
    } else if (Z_TYPE_P(zv) == IS_STRING) {
        zend_long lval;
        double dval;

        switch (is_numeric_string(Z_STRVAL_P(zv), Z_STRLEN_P(zv), &lval, &dval, 1)) {
            case IS_LONG:
                *retval = (int64_t)lval;
                return SUCCESS;
            case IS_DOUBLE:
                *retval = (int64_t)dval;
                return SUCCESS;
        }
    }

    /* If we make it here we have failed */
    return FAILURE;
}