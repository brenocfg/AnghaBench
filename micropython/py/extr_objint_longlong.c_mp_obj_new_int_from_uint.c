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
typedef  int mp_uint_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (int) ; 
 int MP_SMALL_INT_POSITIVE_MASK ; 
 int /*<<< orphan*/  mp_obj_new_int_from_ll (int) ; 

mp_obj_t mp_obj_new_int_from_uint(mp_uint_t value) {
    // SMALL_INT accepts only signed numbers, so make sure the input
    // value fits completely in the small-int positive range.
    if ((value & ~MP_SMALL_INT_POSITIVE_MASK) == 0) {
        return MP_OBJ_NEW_SMALL_INT(value);
    }
    return mp_obj_new_int_from_ll(value);
}