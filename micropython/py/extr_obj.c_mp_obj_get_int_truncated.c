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
 int /*<<< orphan*/  mp_obj_get_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_int_get_truncated (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_int (int /*<<< orphan*/ ) ; 

mp_int_t mp_obj_get_int_truncated(mp_const_obj_t arg) {
    if (mp_obj_is_int(arg)) {
        return mp_obj_int_get_truncated(arg);
    } else {
        return mp_obj_get_int(arg);
    }
}