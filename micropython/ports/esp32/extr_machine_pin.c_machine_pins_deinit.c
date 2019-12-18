#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gpio_num_t ;
struct TYPE_3__ {scalar_t__ id; } ;

/* Variables and functions */
 int MP_ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_isr_handler_remove (scalar_t__) ; 
 TYPE_1__* machine_pin_obj ; 

void machine_pins_deinit(void) {
    for (int i = 0; i < MP_ARRAY_SIZE(machine_pin_obj); ++i) {
        if (machine_pin_obj[i].id != (gpio_num_t)-1) {
            gpio_isr_handler_remove(machine_pin_obj[i].id);
        }
    }
}