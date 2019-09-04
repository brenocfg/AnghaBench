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
typedef  int mp_int_t ;
typedef  scalar_t__ mp_const_obj_t ;

/* Variables and functions */
 int MP_OBJ_SMALL_INT_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  MP_UNARY_OP_INT ; 
 scalar_t__ mp_const_false ; 
 scalar_t__ mp_const_true ; 
 int mp_obj_int_get_checked (scalar_t__) ; 
 scalar_t__ mp_obj_is_small_int (scalar_t__) ; 
 scalar_t__ mp_obj_is_type (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_type_int ; 
 scalar_t__ mp_unary_op (int /*<<< orphan*/ ,scalar_t__) ; 

mp_int_t mp_obj_get_int(mp_const_obj_t arg) {
    // This function essentially performs implicit type conversion to int
    // Note that Python does NOT provide implicit type conversion from
    // float to int in the core expression language, try some_list[1.0].
    if (arg == mp_const_false) {
        return 0;
    } else if (arg == mp_const_true) {
        return 1;
    } else if (mp_obj_is_small_int(arg)) {
        return MP_OBJ_SMALL_INT_VALUE(arg);
    } else if (mp_obj_is_type(arg, &mp_type_int)) {
        return mp_obj_int_get_checked(arg);
    } else {
        mp_obj_t res = mp_unary_op(MP_UNARY_OP_INT, (mp_obj_t)arg);
        return mp_obj_int_get_checked(res);
    }
}