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

/* Variables and functions */
 int /*<<< orphan*/  microbit_display_clear () ; 
 int /*<<< orphan*/  mp_const_none ; 

mp_obj_t microbit_display_clear_func(mp_obj_t self_in) {
    microbit_display_clear();
    return mp_const_none;
}