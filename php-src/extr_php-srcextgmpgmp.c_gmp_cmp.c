#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_long ;
typedef  int zend_bool ;
typedef  int /*<<< orphan*/  mpz_ptr ;
struct TYPE_6__ {scalar_t__ is_used; } ;
typedef  TYPE_1__ gmp_temp_t ;

/* Variables and functions */
 int /*<<< orphan*/  FETCH_GMP_ZVAL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  FETCH_GMP_ZVAL_DEP (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  FREE_GMP_TEMP (TYPE_1__) ; 
 scalar_t__ IS_LONG ; 
 int /*<<< orphan*/  RETURN_LONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpz_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_cmp_si (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gmp_cmp(zval *return_value, zval *a_arg, zval *b_arg) /* {{{ */
{
	mpz_ptr gmpnum_a, gmpnum_b;
	gmp_temp_t temp_a, temp_b;
	zend_bool use_si = 0;
	zend_long res;

	FETCH_GMP_ZVAL(gmpnum_a, a_arg, temp_a);

	if (Z_TYPE_P(b_arg) == IS_LONG) {
		use_si = 1;
		temp_b.is_used = 0;
	} else {
		FETCH_GMP_ZVAL_DEP(gmpnum_b, b_arg, temp_b, temp_a);
	}

	if (use_si) {
		res = mpz_cmp_si(gmpnum_a, Z_LVAL_P(b_arg));
	} else {
		res = mpz_cmp(gmpnum_a, gmpnum_b);
	}

	FREE_GMP_TEMP(temp_a);
	FREE_GMP_TEMP(temp_b);

	RETURN_LONG(res);
}