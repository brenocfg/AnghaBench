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
typedef  int /*<<< orphan*/  (* gmp_unary_op_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  gmp_temp_t ;

/* Variables and functions */
 int /*<<< orphan*/  FETCH_GMP_ZVAL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_GMP_TEMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_GMP_RETVAL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gmp_zval_unary_op(zval *return_value, zval *a_arg, gmp_unary_op_t gmp_op)
{
	mpz_ptr gmpnum_a, gmpnum_result;
	gmp_temp_t temp_a;

	FETCH_GMP_ZVAL(gmpnum_a, a_arg, temp_a);

	INIT_GMP_RETVAL(gmpnum_result);
	gmp_op(gmpnum_result, gmpnum_a);

	FREE_GMP_TEMP(temp_a);
}