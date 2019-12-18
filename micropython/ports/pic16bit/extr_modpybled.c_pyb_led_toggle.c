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
typedef  int /*<<< orphan*/  pyb_led_obj_t ;
typedef  int /*<<< orphan*/ * mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  LED_ID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_toggle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_const_none ; 

mp_obj_t pyb_led_toggle(mp_obj_t self_in) {
    pyb_led_obj_t *self = self_in;
    led_toggle(LED_ID(self));
    return mp_const_none;
}