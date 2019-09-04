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
typedef  int /*<<< orphan*/  MP_STATE_PORT ;

/* Variables and functions */
 int /*<<< orphan*/  mp_const_none ; 
 int pin_class_debug ; 

void pin_init0(void) {
    MP_STATE_PORT(pin_class_mapper) = mp_const_none;
    MP_STATE_PORT(pin_class_map_dict) = mp_const_none;
    pin_class_debug = false;
}