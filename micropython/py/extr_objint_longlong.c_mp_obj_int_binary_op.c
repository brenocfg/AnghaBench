#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mp_obj_t ;
struct TYPE_2__ {long long val; } ;
typedef  TYPE_1__ mp_obj_int_t ;
typedef  int mp_binary_op_t ;

/* Variables and functions */
#define  MP_BINARY_OP_ADD 154 
#define  MP_BINARY_OP_AND 153 
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
#define  MP_BINARY_OP_XOR 128 
 scalar_t__ MP_OBJ_NULL ; 
 long long MP_OBJ_SMALL_INT_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 scalar_t__ mp_obj_float_binary_op (int,long long,scalar_t__) ; 
 scalar_t__ mp_obj_int_binary_op_extra_cases (int,scalar_t__,scalar_t__) ; 
 scalar_t__ mp_obj_is_small_int (scalar_t__) ; 
 scalar_t__ mp_obj_is_type (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_obj_new_bool (int) ; 
 scalar_t__ mp_obj_new_int_from_ll (long long) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 
 int /*<<< orphan*/  mp_raise_msg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_type_ZeroDivisionError ; 
 int /*<<< orphan*/  mp_type_int ; 

mp_obj_t mp_obj_int_binary_op(mp_binary_op_t op, mp_obj_t lhs_in, mp_obj_t rhs_in) {
    long long lhs_val;
    long long rhs_val;

    if (mp_obj_is_small_int(lhs_in)) {
        lhs_val = MP_OBJ_SMALL_INT_VALUE(lhs_in);
    } else {
        assert(mp_obj_is_type(lhs_in, &mp_type_int));
        lhs_val = ((mp_obj_int_t*)lhs_in)->val;
    }

    if (mp_obj_is_small_int(rhs_in)) {
        rhs_val = MP_OBJ_SMALL_INT_VALUE(rhs_in);
    } else if (mp_obj_is_type(rhs_in, &mp_type_int)) {
        rhs_val = ((mp_obj_int_t*)rhs_in)->val;
    } else {
        // delegate to generic function to check for extra cases
        return mp_obj_int_binary_op_extra_cases(op, lhs_in, rhs_in);
    }

    switch (op) {
        case MP_BINARY_OP_ADD:
        case MP_BINARY_OP_INPLACE_ADD:
            return mp_obj_new_int_from_ll(lhs_val + rhs_val);
        case MP_BINARY_OP_SUBTRACT:
        case MP_BINARY_OP_INPLACE_SUBTRACT:
            return mp_obj_new_int_from_ll(lhs_val - rhs_val);
        case MP_BINARY_OP_MULTIPLY:
        case MP_BINARY_OP_INPLACE_MULTIPLY:
            return mp_obj_new_int_from_ll(lhs_val * rhs_val);
        case MP_BINARY_OP_FLOOR_DIVIDE:
        case MP_BINARY_OP_INPLACE_FLOOR_DIVIDE:
            if (rhs_val == 0) {
                goto zero_division;
            }
            return mp_obj_new_int_from_ll(lhs_val / rhs_val);
        case MP_BINARY_OP_MODULO:
        case MP_BINARY_OP_INPLACE_MODULO:
            if (rhs_val == 0) {
                goto zero_division;
            }
            return mp_obj_new_int_from_ll(lhs_val % rhs_val);

        case MP_BINARY_OP_AND:
        case MP_BINARY_OP_INPLACE_AND:
            return mp_obj_new_int_from_ll(lhs_val & rhs_val);
        case MP_BINARY_OP_OR:
        case MP_BINARY_OP_INPLACE_OR:
            return mp_obj_new_int_from_ll(lhs_val | rhs_val);
        case MP_BINARY_OP_XOR:
        case MP_BINARY_OP_INPLACE_XOR:
            return mp_obj_new_int_from_ll(lhs_val ^ rhs_val);

        case MP_BINARY_OP_LSHIFT:
        case MP_BINARY_OP_INPLACE_LSHIFT:
            return mp_obj_new_int_from_ll(lhs_val << (int)rhs_val);
        case MP_BINARY_OP_RSHIFT:
        case MP_BINARY_OP_INPLACE_RSHIFT:
            return mp_obj_new_int_from_ll(lhs_val >> (int)rhs_val);

        case MP_BINARY_OP_POWER:
        case MP_BINARY_OP_INPLACE_POWER: {
            if (rhs_val < 0) {
                #if MICROPY_PY_BUILTINS_FLOAT
                return mp_obj_float_binary_op(op, lhs_val, rhs_in);
                #else
                mp_raise_ValueError("negative power with no float support");
                #endif
            }
            long long ans = 1;
            while (rhs_val > 0) {
                if (rhs_val & 1) {
                    ans *= lhs_val;
                }
                if (rhs_val == 1) {
                    break;
                }
                rhs_val /= 2;
                lhs_val *= lhs_val;
            }
            return mp_obj_new_int_from_ll(ans);
        }

        case MP_BINARY_OP_LESS:
            return mp_obj_new_bool(lhs_val < rhs_val);
        case MP_BINARY_OP_MORE:
            return mp_obj_new_bool(lhs_val > rhs_val);
        case MP_BINARY_OP_LESS_EQUAL:
            return mp_obj_new_bool(lhs_val <= rhs_val);
        case MP_BINARY_OP_MORE_EQUAL:
            return mp_obj_new_bool(lhs_val >= rhs_val);
        case MP_BINARY_OP_EQUAL:
            return mp_obj_new_bool(lhs_val == rhs_val);

        default:
            return MP_OBJ_NULL; // op not supported
    }

zero_division:
    mp_raise_msg(&mp_type_ZeroDivisionError, "divide by zero");
}