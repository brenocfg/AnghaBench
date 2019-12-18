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
 int /*<<< orphan*/  UDD_STATE_SUSPEND ; 
 int /*<<< orphan*/  udd_sleep_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device ; 
 int /*<<< orphan*/  usb_device_detach (int /*<<< orphan*/ *) ; 

void udd_detach(void) {
    usb_device_detach(&usb_device);
    udd_sleep_mode(UDD_STATE_SUSPEND);
}