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
typedef  int /*<<< orphan*/  mpz_ptr ;
typedef  int /*<<< orphan*/  (* gmp_unary_ui_op_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_GMP_RETVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_get_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void gmp_zval_unary_ui_op(zval *return_value, zval *a_arg, gmp_unary_ui_op_t gmp_op)
{
	mpz_ptr gmpnum_result;

	INIT_GMP_RETVAL(gmpnum_result);
	gmp_op(gmpnum_result, zval_get_long(a_arg));
}