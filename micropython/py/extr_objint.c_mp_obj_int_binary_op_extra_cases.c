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
typedef  scalar_t__ mp_obj_t ;
typedef  scalar_t__ mp_binary_op_t ;

/* Variables and functions */
 scalar_t__ MP_BINARY_OP_MULTIPLY ; 
 scalar_t__ MP_OBJ_NEW_SMALL_INT (int) ; 
 scalar_t__ MP_OBJ_NULL ; 
 scalar_t__ mp_binary_op (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mp_const_false ; 
 scalar_t__ mp_const_true ; 
 scalar_t__ mp_obj_is_str_or_bytes (scalar_t__) ; 
 scalar_t__ mp_obj_is_type (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_type_list ; 
 int /*<<< orphan*/  mp_type_tuple ; 

mp_obj_t mp_obj_int_binary_op_extra_cases(mp_binary_op_t op, mp_obj_t lhs_in, mp_obj_t rhs_in) {
    if (rhs_in == mp_const_false) {
        // false acts as 0
        return mp_binary_op(op, lhs_in, MP_OBJ_NEW_SMALL_INT(0));
    } else if (rhs_in == mp_const_true) {
        // true acts as 0
        return mp_binary_op(op, lhs_in, MP_OBJ_NEW_SMALL_INT(1));
    } else if (op == MP_BINARY_OP_MULTIPLY) {
        if (mp_obj_is_str_or_bytes(rhs_in) || mp_obj_is_type(rhs_in, &mp_type_tuple) || mp_obj_is_type(rhs_in, &mp_type_list)) {
            // multiply is commutative for these types, so delegate to them
            return mp_binary_op(op, rhs_in, lhs_in);
        }
    }
    return MP_OBJ_NULL; // op not supported
}