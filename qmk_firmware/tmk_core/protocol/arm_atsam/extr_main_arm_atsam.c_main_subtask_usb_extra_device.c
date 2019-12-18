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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  USB_HandleExtraDevice () ; 
 scalar_t__ timer_read64 () ; 

void main_subtask_usb_extra_device(void) {
    static uint64_t next_usb_checkup = 0;

    if (timer_read64() > next_usb_checkup) {
        next_usb_checkup = timer_read64() + 10;

        USB_HandleExtraDevice();
    }
}