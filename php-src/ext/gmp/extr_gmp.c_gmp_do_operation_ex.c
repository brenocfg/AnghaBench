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
typedef  int zend_uchar ;

/* Variables and functions */
 int /*<<< orphan*/  DO_BINARY_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_BINARY_UI_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_BINARY_UI_OP_EX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DO_UNARY_OP (int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 int SUCCESS ; 
#define  ZEND_ADD 139 
#define  ZEND_BW_AND 138 
#define  ZEND_BW_NOT 137 
#define  ZEND_BW_OR 136 
#define  ZEND_BW_XOR 135 
#define  ZEND_DIV 134 
#define  ZEND_MOD 133 
#define  ZEND_MUL 132 
#define  ZEND_POW 131 
#define  ZEND_SL 130 
#define  ZEND_SR 129 
#define  ZEND_SUB 128 
 int /*<<< orphan*/  mpz_add ; 
 int /*<<< orphan*/  mpz_and ; 
 int /*<<< orphan*/  mpz_com ; 
 int /*<<< orphan*/  mpz_fdiv_q_2exp ; 
 int /*<<< orphan*/  mpz_ior ; 
 int /*<<< orphan*/  mpz_mod ; 
 int /*<<< orphan*/  mpz_mod_ui ; 
 int /*<<< orphan*/  mpz_mul ; 
 int /*<<< orphan*/  mpz_mul_2exp ; 
 int /*<<< orphan*/  mpz_pow_ui ; 
 int /*<<< orphan*/  mpz_sub ; 
 int /*<<< orphan*/  mpz_tdiv_q ; 
 int /*<<< orphan*/  mpz_tdiv_q_ui ; 
 int /*<<< orphan*/  mpz_xor ; 
 int /*<<< orphan*/  shift_operator_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gmp_do_operation_ex(zend_uchar opcode, zval *result, zval *op1, zval *op2) /* {{{ */
{
	switch (opcode) {
	case ZEND_ADD:
		DO_BINARY_UI_OP(mpz_add);
	case ZEND_SUB:
		DO_BINARY_UI_OP(mpz_sub);
	case ZEND_MUL:
		DO_BINARY_UI_OP(mpz_mul);
	case ZEND_POW:
		shift_operator_helper(mpz_pow_ui, result, op1, op2);
		return SUCCESS;
	case ZEND_DIV:
		DO_BINARY_UI_OP_EX(mpz_tdiv_q, mpz_tdiv_q_ui, 1);
	case ZEND_MOD:
		DO_BINARY_UI_OP_EX(mpz_mod, mpz_mod_ui, 1);
	case ZEND_SL:
		shift_operator_helper(mpz_mul_2exp, result, op1, op2);
		return SUCCESS;
	case ZEND_SR:
		shift_operator_helper(mpz_fdiv_q_2exp, result, op1, op2);
		return SUCCESS;
	case ZEND_BW_OR:
		DO_BINARY_OP(mpz_ior);
	case ZEND_BW_AND:
		DO_BINARY_OP(mpz_and);
	case ZEND_BW_XOR:
		DO_BINARY_OP(mpz_xor);
	case ZEND_BW_NOT:
		DO_UNARY_OP(mpz_com);

	default:
		return FAILURE;
	}
}