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
struct TYPE_2__ {int /*<<< orphan*/  level; scalar_t__ enable; } ;

/* Variables and functions */
 int ROWS_PER_HAND ; 
 size_t SERIAL_LED_ADDR ; 
 TYPE_1__ backlight_config ; 
 scalar_t__ isLeftHand ; 
 int /*<<< orphan*/ * matrix ; 
 int /*<<< orphan*/ * serial_master_buffer ; 
 int /*<<< orphan*/ * serial_slave_buffer ; 
 scalar_t__ serial_update_buffers () ; 

int serial_transaction(void) {
    int slaveOffset = (isLeftHand) ? (ROWS_PER_HAND) : 0;

    if (serial_update_buffers()) {
        return 1;
    }

    for (int i = 0; i < ROWS_PER_HAND; ++i) {
        matrix[slaveOffset+i] = serial_slave_buffer[i];
    }

#ifdef BACKLIGHT_ENABLE
    // Write backlight level for slave to read
    serial_master_buffer[SERIAL_LED_ADDR] = backlight_config.enable ? backlight_config.level : 0;
#endif
    return 0;
}