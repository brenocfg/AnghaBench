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
 int DDRD ; 
 int MCUSR ; 
 int PORTD ; 
 int /*<<< orphan*/  USB_Device_EnableSOFEvents () ; 
 int /*<<< orphan*/  USB_Disable () ; 
 int /*<<< orphan*/  USB_Init () ; 
 int WDRF ; 
 int /*<<< orphan*/  clock_div_1 ; 
 int /*<<< orphan*/  clock_prescale_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_set_sendchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendchar_func ; 
 int /*<<< orphan*/  wdt_disable () ; 

__attribute__((used)) static void SetupHardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
    print_set_sendchar(sendchar_func);

    // SUART PD0:output, PD1:input
    DDRD |= (1<<0);
    PORTD |= (1<<0);
    DDRD &= ~(1<<1);
    PORTD |= (1<<1);
}