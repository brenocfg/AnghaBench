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

/* Variables and functions */
 int /*<<< orphan*/  pointing_device_send () ; 

__attribute__((weak)) void pointing_device_task(void) {
    // gather info and put it in:
    // mouseReport.x = 127 max -127 min
    // mouseReport.y = 127 max -127 min
    // mouseReport.v = 127 max -127 min (scroll vertical)
    // mouseReport.h = 127 max -127 min (scroll horizontal)
    // mouseReport.buttons = 0x1F (decimal 31, binary 00011111) max (bitmask for mouse buttons 1-5, 1 is rightmost, 5 is leftmost) 0x00 min
    // send the report
    pointing_device_send();
}