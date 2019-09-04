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
typedef  int /*<<< orphan*/  mpz_ptr ;
typedef  int /*<<< orphan*/  gmp_ulong ;
typedef  int /*<<< orphan*/  gmp_temp_t ;
typedef  int /*<<< orphan*/  (* gmp_binary_ui_op_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  FETCH_GMP_ZVAL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_GMP_TEMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_GMP_RETVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETVAL_FALSE ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zval_get_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shift_operator_helper(gmp_binary_ui_op_t op, zval *return_value, zval *op1, zval *op2) {
	zend_long shift = zval_get_long(op2);

	if (shift < 0) {
		php_error_docref(NULL, E_WARNING, "Shift cannot be negative");
		RETVAL_FALSE;
	} else {
		mpz_ptr gmpnum_op, gmpnum_result;
		gmp_temp_t temp;

		FETCH_GMP_ZVAL(gmpnum_op, op1, temp);
		INIT_GMP_RETVAL(gmpnum_result);
		op(gmpnum_result, gmpnum_op, (gmp_ulong) shift);
		FREE_GMP_TEMP(temp);
	}
}