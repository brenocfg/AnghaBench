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
 int /*<<< orphan*/  ROW_PINS_MASK ; 
 scalar_t__ mp_const_none ; 
 int /*<<< orphan*/  nrf_gpio_port_out_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mp_obj_t microbit_display_off_func(mp_obj_t obj) {
    microbit_display_obj_t *self = (microbit_display_obj_t*)obj;
    /* Disable the display loop.  This will pause any animations in progress.
     * It will not prevent a user from attempting to modify the state, but
     * modifications will not appear to have any effect until the display loop
     * is re-enabled. */
    self->active = false;
    /* Disable the row strobes, allowing the columns to be used freely for
     * GPIO. */
    nrf_gpio_port_out_clear(0, ROW_PINS_MASK);
    /* Free pins for other uses */
/*
    microbit_obj_pin_free(&microbit_p3_obj);
    microbit_obj_pin_free(&microbit_p4_obj);
    microbit_obj_pin_free(&microbit_p6_obj);
    microbit_obj_pin_free(&microbit_p7_obj);
    microbit_obj_pin_free(&microbit_p9_obj);
    microbit_obj_pin_free(&microbit_p10_obj);
*/
    return mp_const_none;
}