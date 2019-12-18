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
 int OTGPADE ; 
 int USBCON ; 
 int USBSTA ; 
 int VBUS ; 
 scalar_t__ waitForUsb () ; 
 int /*<<< orphan*/  wait_us (int) ; 

__attribute__((weak)) bool is_keyboard_master(void) {
    static enum { UNKNOWN, MASTER, SLAVE } usbstate = UNKNOWN;

    // only check once, as this is called often
    if (usbstate == UNKNOWN) {
#if defined(SPLIT_USB_DETECT)
        usbstate = waitForUsb() ? MASTER : SLAVE;
#elif defined(__AVR__)
        USBCON |= (1 << OTGPADE);  // enables VBUS pad
        wait_us(5);

        usbstate = (USBSTA & (1 << VBUS)) ? MASTER : SLAVE;  // checks state of VBUS
#else
        usbstate = MASTER;
#endif
    }

    return (usbstate == MASTER);
}