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
typedef  int /*<<< orphan*/  usbep_t ;
typedef  int /*<<< orphan*/  USBDriver ;

/* Variables and functions */

void kbd_in_cb(USBDriver *usbp, usbep_t ep) {
    /* STUB */
    (void)usbp;
    (void)ep;
}