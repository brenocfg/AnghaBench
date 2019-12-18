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
typedef  int /*<<< orphan*/  mp_uint_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  scalar_t__ mp_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_is_obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_new_int (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_new_int_from_uint (int /*<<< orphan*/ ) ; 

mp_obj_t mp_obj_id(mp_obj_t o_in) {
    mp_int_t id = (mp_int_t)o_in;
    if (!mp_obj_is_obj(o_in)) {
        return mp_obj_new_int(id);
    } else if (id >= 0) {
        // Many OSes and CPUs have affinity for putting "user" memories
        // into low half of address space, and "system" into upper half.
        // We're going to take advantage of that and return small int
        // (signed) for such "user" addresses.
        return MP_OBJ_NEW_SMALL_INT(id);
    } else {
        // If that didn't work, well, let's return long int, just as
        // a (big) positive value, so it will never clash with the range
        // of small int returned in previous case.
        return mp_obj_new_int_from_uint((mp_uint_t)id);
    }
}