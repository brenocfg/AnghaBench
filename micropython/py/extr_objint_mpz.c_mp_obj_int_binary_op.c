#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpz_t ;
typedef  int /*<<< orphan*/  mpz_dig_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_4__ {int /*<<< orphan*/  mpz; } ;
typedef  TYPE_1__ mp_obj_int_t ;
typedef  int /*<<< orphan*/  mp_int_t ;
typedef  int mp_float_t ;
typedef  int mp_binary_op_t ;

/* Variables and functions */
 int MPZ_NUM_DIG_FOR_INT ; 
#define  MP_BINARY_OP_ADD 154 
#define  MP_BINARY_OP_AND 153 
 int MP_BINARY_OP_CONTAINS ; 
 int MP_BINARY_OP_DIVMOD ; 
#define  MP_BINARY_OP_EQUAL 152 
#define  MP_BINARY_OP_FLOOR_DIVIDE 151 
#define  MP_BINARY_OP_INPLACE_ADD 150 
#define  MP_BINARY_OP_INPLACE_AND 149 
#define  MP_BINARY_OP_INPLACE_FLOOR_DIVIDE 148 
#define  MP_BINARY_OP_INPLACE_LSHIFT 147 
#define  MP_BINARY_OP_INPLACE_MODULO 146 
#define  MP_BINARY_OP_INPLACE_MULTIPLY 145 
#define  MP_BINARY_OP_INPLACE_OR 144 
#define  MP_BINARY_OP_INPLACE_POWER 143 
#define  MP_BINARY_OP_INPLACE_RSHIFT 142 
#define  MP_BINARY_OP_INPLACE_SUBTRACT 141 
 int MP_BINARY_OP_INPLACE_TRUE_DIVIDE ; 
#define  MP_BINARY_OP_INPLACE_XOR 140 
#define  MP_BINARY_OP_LESS 139 
#define  MP_BINARY_OP_LESS_EQUAL 138 
#define  MP_BINARY_OP_LSHIFT 137 
#define  MP_BINARY_OP_MODULO 136 
#define  MP_BINARY_OP_MORE 135 
#define  MP_BINARY_OP_MORE_EQUAL 134 
#define  MP_BINARY_OP_MULTIPLY 133 
#define  MP_BINARY_OP_OR 132 
#define  MP_BINARY_OP_POWER 131 
#define  MP_BINARY_OP_RSHIFT 130 
#define  MP_BINARY_OP_SUBTRACT 129 
 int MP_BINARY_OP_TRUE_DIVIDE ; 
#define  MP_BINARY_OP_XOR 128 
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_OBJ_NULL ; 
 int /*<<< orphan*/  MP_OBJ_SMALL_INT_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_obj_complex_binary_op (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_float_binary_op (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_int_binary_op_extra_cases (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_int_get_checked (int /*<<< orphan*/ ) ; 
 TYPE_1__* mp_obj_int_new_mpz () ; 
 scalar_t__ mp_obj_is_float (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_small_int (int /*<<< orphan*/ ) ; 
 int mp_obj_is_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_new_bool (int) ; 
 int /*<<< orphan*/  mp_obj_new_float (int) ; 
 int /*<<< orphan*/  mp_obj_new_tuple (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 
 int /*<<< orphan*/  mp_raise_msg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_type_ZeroDivisionError ; 
 int /*<<< orphan*/  mp_type_complex ; 
 int /*<<< orphan*/  mp_type_int ; 
 int /*<<< orphan*/  mpz_add_inpl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpz_and_inpl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int mpz_as_float (int /*<<< orphan*/  const*) ; 
 int mpz_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpz_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpz_divmod_inpl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpz_init_fixed_from_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_init_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpz_is_neg (int /*<<< orphan*/  const*) ; 
 scalar_t__ mpz_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpz_mul_inpl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpz_or_inpl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpz_pow_inpl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpz_shl_inpl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_shr_inpl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_sub_inpl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpz_xor_inpl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

mp_obj_t mp_obj_int_binary_op(mp_binary_op_t op, mp_obj_t lhs_in, mp_obj_t rhs_in) {
    const mpz_t *zlhs;
    const mpz_t *zrhs;
    mpz_t z_int;
    mpz_dig_t z_int_dig[MPZ_NUM_DIG_FOR_INT];

    // lhs could be a small int (eg small-int + mpz)
    if (mp_obj_is_small_int(lhs_in)) {
        mpz_init_fixed_from_int(&z_int, z_int_dig, MPZ_NUM_DIG_FOR_INT, MP_OBJ_SMALL_INT_VALUE(lhs_in));
        zlhs = &z_int;
    } else {
        assert(mp_obj_is_type(lhs_in, &mp_type_int));
        zlhs = &((mp_obj_int_t*)MP_OBJ_TO_PTR(lhs_in))->mpz;
    }

    // if rhs is small int, then lhs was not (otherwise mp_binary_op handles it)
    if (mp_obj_is_small_int(rhs_in)) {
        mpz_init_fixed_from_int(&z_int, z_int_dig, MPZ_NUM_DIG_FOR_INT, MP_OBJ_SMALL_INT_VALUE(rhs_in));
        zrhs = &z_int;
    } else if (mp_obj_is_type(rhs_in, &mp_type_int)) {
        zrhs = &((mp_obj_int_t*)MP_OBJ_TO_PTR(rhs_in))->mpz;
#if MICROPY_PY_BUILTINS_FLOAT
    } else if (mp_obj_is_float(rhs_in)) {
        return mp_obj_float_binary_op(op, mpz_as_float(zlhs), rhs_in);
#if MICROPY_PY_BUILTINS_COMPLEX
    } else if (mp_obj_is_type(rhs_in, &mp_type_complex)) {
        return mp_obj_complex_binary_op(op, mpz_as_float(zlhs), 0, rhs_in);
#endif
#endif
    } else {
        // delegate to generic function to check for extra cases
        return mp_obj_int_binary_op_extra_cases(op, lhs_in, rhs_in);
    }

#if MICROPY_PY_BUILTINS_FLOAT
    if (op == MP_BINARY_OP_TRUE_DIVIDE || op == MP_BINARY_OP_INPLACE_TRUE_DIVIDE) {
        if (mpz_is_zero(zrhs)) {
            goto zero_division_error;
        }
        mp_float_t flhs = mpz_as_float(zlhs);
        mp_float_t frhs = mpz_as_float(zrhs);
        return mp_obj_new_float(flhs / frhs);
    } else
#endif

    if (op >= MP_BINARY_OP_INPLACE_OR && op < MP_BINARY_OP_CONTAINS) {
        mp_obj_int_t *res = mp_obj_int_new_mpz();

        switch (op) {
            case MP_BINARY_OP_ADD:
            case MP_BINARY_OP_INPLACE_ADD:
                mpz_add_inpl(&res->mpz, zlhs, zrhs);
                break;
            case MP_BINARY_OP_SUBTRACT:
            case MP_BINARY_OP_INPLACE_SUBTRACT:
                mpz_sub_inpl(&res->mpz, zlhs, zrhs);
                break;
            case MP_BINARY_OP_MULTIPLY:
            case MP_BINARY_OP_INPLACE_MULTIPLY:
                mpz_mul_inpl(&res->mpz, zlhs, zrhs);
                break;
            case MP_BINARY_OP_FLOOR_DIVIDE:
            case MP_BINARY_OP_INPLACE_FLOOR_DIVIDE: {
                if (mpz_is_zero(zrhs)) {
                    zero_division_error:
                    mp_raise_msg(&mp_type_ZeroDivisionError, "divide by zero");
                }
                mpz_t rem; mpz_init_zero(&rem);
                mpz_divmod_inpl(&res->mpz, &rem, zlhs, zrhs);
                mpz_deinit(&rem);
                break;
            }
            case MP_BINARY_OP_MODULO:
            case MP_BINARY_OP_INPLACE_MODULO: {
                if (mpz_is_zero(zrhs)) {
                    goto zero_division_error;
                }
                mpz_t quo; mpz_init_zero(&quo);
                mpz_divmod_inpl(&quo, &res->mpz, zlhs, zrhs);
                mpz_deinit(&quo);
                break;
            }

            case MP_BINARY_OP_AND:
            case MP_BINARY_OP_INPLACE_AND:
                mpz_and_inpl(&res->mpz, zlhs, zrhs);
                break;
            case MP_BINARY_OP_OR:
            case MP_BINARY_OP_INPLACE_OR:
                mpz_or_inpl(&res->mpz, zlhs, zrhs);
                break;
            case MP_BINARY_OP_XOR:
            case MP_BINARY_OP_INPLACE_XOR:
                mpz_xor_inpl(&res->mpz, zlhs, zrhs);
                break;

            case MP_BINARY_OP_LSHIFT:
            case MP_BINARY_OP_INPLACE_LSHIFT:
            case MP_BINARY_OP_RSHIFT:
            case MP_BINARY_OP_INPLACE_RSHIFT: {
                mp_int_t irhs = mp_obj_int_get_checked(rhs_in);
                if (irhs < 0) {
                    mp_raise_ValueError("negative shift count");
                }
                if (op == MP_BINARY_OP_LSHIFT || op == MP_BINARY_OP_INPLACE_LSHIFT) {
                    mpz_shl_inpl(&res->mpz, zlhs, irhs);
                } else {
                    mpz_shr_inpl(&res->mpz, zlhs, irhs);
                }
                break;
            }

            case MP_BINARY_OP_POWER:
            case MP_BINARY_OP_INPLACE_POWER:
                if (mpz_is_neg(zrhs)) {
                    #if MICROPY_PY_BUILTINS_FLOAT
                    return mp_obj_float_binary_op(op, mpz_as_float(zlhs), rhs_in);
                    #else
                    mp_raise_ValueError("negative power with no float support");
                    #endif
                }
                mpz_pow_inpl(&res->mpz, zlhs, zrhs);
                break;

            default: {
                assert(op == MP_BINARY_OP_DIVMOD);
                if (mpz_is_zero(zrhs)) {
                    goto zero_division_error;
                }
                mp_obj_int_t *quo = mp_obj_int_new_mpz();
                mpz_divmod_inpl(&quo->mpz, &res->mpz, zlhs, zrhs);
                mp_obj_t tuple[2] = {MP_OBJ_FROM_PTR(quo), MP_OBJ_FROM_PTR(res)};
                return mp_obj_new_tuple(2, tuple);
            }
        }

        return MP_OBJ_FROM_PTR(res);

    } else {
        int cmp = mpz_cmp(zlhs, zrhs);
        switch (op) {
            case MP_BINARY_OP_LESS:
                return mp_obj_new_bool(cmp < 0);
            case MP_BINARY_OP_MORE:
                return mp_obj_new_bool(cmp > 0);
            case MP_BINARY_OP_LESS_EQUAL:
                return mp_obj_new_bool(cmp <= 0);
            case MP_BINARY_OP_MORE_EQUAL:
                return mp_obj_new_bool(cmp >= 0);
            case MP_BINARY_OP_EQUAL:
                return mp_obj_new_bool(cmp == 0);

            default:
                return MP_OBJ_NULL; // op not supported
        }
    }
}