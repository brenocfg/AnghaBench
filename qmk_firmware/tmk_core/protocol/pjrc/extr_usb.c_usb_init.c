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
 int EORSTE ; 
 int /*<<< orphan*/  HW_CONFIG () ; 
 int PLLCSR ; 
 int /*<<< orphan*/  PLL_CONFIG () ; 
 int PLOCK ; 
 int SOFE ; 
 int SUSPE ; 
 scalar_t__ UDCON ; 
 int UDIEN ; 
 int /*<<< orphan*/  USB_CONFIG () ; 
 int /*<<< orphan*/  USB_FREEZE () ; 
 int WAKEUPE ; 
 int /*<<< orphan*/  sei () ; 
 int suspend ; 
 scalar_t__ usb_configuration ; 

void usb_init(void) {
    HW_CONFIG();
    USB_FREEZE();  // enable USB
    PLL_CONFIG();  // config PLL
    while (!(PLLCSR & (1 << PLOCK)))
        ;                   // wait for PLL lock
    USB_CONFIG();           // start USB clock
    UDCON             = 0;  // enable attach resistor
    usb_configuration = 0;
    suspend           = false;
    UDIEN             = (1 << EORSTE) | (1 << SOFE) | (1 << SUSPE) | (1 << WAKEUPE);
    sei();
}