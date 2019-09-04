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
typedef  int /*<<< orphan*/ * mpz_ptr ;
typedef  int /*<<< orphan*/  gmp_ulong ;
struct TYPE_6__ {scalar_t__ is_used; } ;
typedef  TYPE_1__ gmp_temp_t ;
typedef  int /*<<< orphan*/  (* gmp_binary_ui_op2_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  (* gmp_binary_op2_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  FETCH_GMP_ZVAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  FETCH_GMP_ZVAL_DEP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  FREE_GMP_TEMP (TYPE_1__) ; 
 scalar_t__ IS_LONG ; 
 int /*<<< orphan*/  RETURN_FALSE ; 
 scalar_t__ Z_LVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gmp_create (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mpz_cmp_ui (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void gmp_zval_binary_ui_op2(zval *return_value, zval *a_arg, zval *b_arg, gmp_binary_op2_t gmp_op, gmp_binary_ui_op2_t gmp_ui_op, int check_b_zero)
{
	mpz_ptr gmpnum_a, gmpnum_b, gmpnum_result1, gmpnum_result2;
	gmp_temp_t temp_a, temp_b;
	zval result1, result2;

	FETCH_GMP_ZVAL(gmpnum_a, a_arg, temp_a);

	if (gmp_ui_op && Z_TYPE_P(b_arg) == IS_LONG && Z_LVAL_P(b_arg) >= 0) {
		gmpnum_b = NULL;
		temp_b.is_used = 0;
	} else {
		FETCH_GMP_ZVAL_DEP(gmpnum_b, b_arg, temp_b, temp_a);
	}

	if (check_b_zero) {
		int b_is_zero = 0;
		if (!gmpnum_b) {
			b_is_zero = (Z_LVAL_P(b_arg) == 0);
		} else {
			b_is_zero = !mpz_cmp_ui(gmpnum_b, 0);
		}

		if (b_is_zero) {
			php_error_docref(NULL, E_WARNING, "Zero operand not allowed");
			FREE_GMP_TEMP(temp_a);
			FREE_GMP_TEMP(temp_b);
			RETURN_FALSE;
		}
	}

	gmp_create(&result1, &gmpnum_result1);
	gmp_create(&result2, &gmpnum_result2);

	array_init(return_value);
	add_next_index_zval(return_value, &result1);
	add_next_index_zval(return_value, &result2);

	if (!gmpnum_b) {
		gmp_ui_op(gmpnum_result1, gmpnum_result2, gmpnum_a, (gmp_ulong) Z_LVAL_P(b_arg));
	} else {
		gmp_op(gmpnum_result1, gmpnum_result2, gmpnum_a, gmpnum_b);
	}

	FREE_GMP_TEMP(temp_a);
	FREE_GMP_TEMP(temp_b);
}