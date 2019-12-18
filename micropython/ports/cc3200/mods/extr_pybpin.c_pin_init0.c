#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  int /*<<< orphan*/  pin_obj_t ;
struct TYPE_5__ {int used; TYPE_1__* table; } ;
typedef  TYPE_2__ mp_map_t ;
struct TYPE_6__ {TYPE_2__ map; } ;
struct TYPE_4__ {scalar_t__ value; } ;

/* Variables and functions */
 TYPE_3__ pin_board_pins_locals_dict ; 
 int /*<<< orphan*/  pin_deassign (int /*<<< orphan*/ *) ; 

void pin_init0(void) {
// this initalization also reconfigures the JTAG/SWD pins
#ifndef DEBUG
    // assign all pins to the GPIO module so that peripherals can be connected to any
    // pins without conflicts after a soft reset
    const mp_map_t *named_map = &pin_board_pins_locals_dict.map;
    for (uint i = 0; i < named_map->used - 1; i++) {
        pin_obj_t * pin = (pin_obj_t *)named_map->table[i].value;
        pin_deassign (pin);
    }
#endif
}