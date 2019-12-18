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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  usbDeviceConnect () ; 
 int /*<<< orphan*/  usbDeviceDisconnect () ; 
 int /*<<< orphan*/  usbInit () ; 
 int /*<<< orphan*/  wdt_reset () ; 

__attribute__((used)) static void initForUsbConnectivity(void) {
    uint8_t i = 0;

    usbInit();
    /* enforce USB re-enumerate: */
    usbDeviceDisconnect(); /* do this while interrupts are disabled */
    while (--i) {          /* fake USB disconnect for > 250 ms */
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();
    sei();
}