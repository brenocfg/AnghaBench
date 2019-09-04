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
 int /*<<< orphan*/  mp_hal_pin_low (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_hal_pin_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pin_G6 ; 

void NUCLEO_H743ZI_board_early_init(void) {
    // Turn off the USB switch
    #define USB_PowerSwitchOn pin_G6
    mp_hal_pin_output(USB_PowerSwitchOn);
    mp_hal_pin_low(USB_PowerSwitchOn);
}