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
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  mp_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (int /*<<< orphan*/ ) ; 
 scalar_t__ MP_SMALL_INT_FITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_const_none ; 
 int /*<<< orphan*/  mp_raise_msg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_type_OverflowError ; 

mp_obj_t mp_obj_new_int(mp_int_t value) {
    if (MP_SMALL_INT_FITS(value)) {
        return MP_OBJ_NEW_SMALL_INT(value);
    }
    mp_raise_msg(&mp_type_OverflowError, "small int overflow");
    return mp_const_none;
}