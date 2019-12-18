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
typedef  int mp_int_t ;
typedef  scalar_t__ mp_const_obj_t ;

/* Variables and functions */
 int MP_OBJ_SMALL_INT_VALUE (scalar_t__) ; 
 scalar_t__ mp_const_false ; 
 scalar_t__ mp_const_true ; 
 int mp_obj_int_get_checked (scalar_t__) ; 
 scalar_t__ mp_obj_is_small_int (scalar_t__) ; 
 scalar_t__ mp_obj_is_type (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_type_int ; 

bool mp_obj_get_int_maybe(mp_const_obj_t arg, mp_int_t *value) {
    if (arg == mp_const_false) {
        *value = 0;
    } else if (arg == mp_const_true) {
        *value = 1;
    } else if (mp_obj_is_small_int(arg)) {
        *value = MP_OBJ_SMALL_INT_VALUE(arg);
    } else if (mp_obj_is_type(arg, &mp_type_int)) {
        *value = mp_obj_int_get_checked(arg);
    } else {
        return false;
    }
    return true;
}