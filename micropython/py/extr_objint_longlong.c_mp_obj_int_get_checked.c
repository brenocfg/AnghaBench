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
typedef  int /*<<< orphan*/  mp_int_t ;
typedef  int /*<<< orphan*/  mp_const_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_obj_int_get_truncated (int /*<<< orphan*/ ) ; 

mp_int_t mp_obj_int_get_checked(mp_const_obj_t self_in) {
    // TODO: Check overflow
    return mp_obj_int_get_truncated(self_in);
}