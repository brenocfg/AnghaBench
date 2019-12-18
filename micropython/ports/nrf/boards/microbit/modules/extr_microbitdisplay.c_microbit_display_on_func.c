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
struct TYPE_2__ {int active; } ;
typedef  TYPE_1__ microbit_display_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  microbit_display_init () ; 
 scalar_t__ mp_const_none ; 

mp_obj_t microbit_display_on_func(mp_obj_t obj) {
    microbit_display_obj_t *self = (microbit_display_obj_t*)obj;
    /* Try to reclaim the pins we need */
/*
    microbit_obj_pin_fail_if_cant_acquire(&microbit_p3_obj);
    microbit_obj_pin_fail_if_cant_acquire(&microbit_p4_obj);
    microbit_obj_pin_fail_if_cant_acquire(&microbit_p6_obj);
    microbit_obj_pin_fail_if_cant_acquire(&microbit_p7_obj);
    microbit_obj_pin_fail_if_cant_acquire(&microbit_p9_obj);
    microbit_obj_pin_fail_if_cant_acquire(&microbit_p10_obj);
    microbit_obj_pin_acquire(&microbit_p3_obj, microbit_pin_mode_display);
    microbit_obj_pin_acquire(&microbit_p4_obj, microbit_pin_mode_display);
    microbit_obj_pin_acquire(&microbit_p6_obj, microbit_pin_mode_display);
    microbit_obj_pin_acquire(&microbit_p7_obj, microbit_pin_mode_display);
    microbit_obj_pin_acquire(&microbit_p9_obj, microbit_pin_mode_display);
    microbit_obj_pin_acquire(&microbit_p10_obj, microbit_pin_mode_display);
*/
    /* Make sure all pins are in the correct state */
    microbit_display_init();
    /* Re-enable the display loop.  This will resume any animations in
     * progress and display any static image. */
    self->active = true;
    return mp_const_none;
}