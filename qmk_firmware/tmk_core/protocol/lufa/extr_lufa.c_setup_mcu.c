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
 int CLKPCE ; 
 int CLKPR ; 
 int CLKPS0 ; 
 int CLKPS1 ; 
 int CLKPS2 ; 
 int CLKPS3 ; 
 int MCUSR ; 
 int WDRF ; 
 int /*<<< orphan*/  wdt_disable () ; 

__attribute__((used)) static void setup_mcu(void) {
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    // clock_prescale_set(clock_div_1);

    CLKPR = (1 << CLKPCE);
    CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
}