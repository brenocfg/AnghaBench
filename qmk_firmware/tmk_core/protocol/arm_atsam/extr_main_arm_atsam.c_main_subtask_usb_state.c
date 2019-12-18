#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ reg; } ;
struct TYPE_5__ {TYPE_1__ FSMSTATUS; } ;
struct TYPE_6__ {TYPE_2__ DEVICE; } ;

/* Variables and functions */
 TYPE_3__* USB ; 
 scalar_t__ USB_FSMSTATUS_FSMSTATE_ON_Val ; 
 scalar_t__ USB_FSMSTATUS_FSMSTATE_SLEEP_Val ; 
 scalar_t__ USB_FSMSTATUS_FSMSTATE_SUSPEND_Val ; 
 scalar_t__ g_usb_state ; 
 int /*<<< orphan*/  suspend_power_down () ; 
 int /*<<< orphan*/  suspend_wakeup_init () ; 
 scalar_t__ timer_read64 () ; 

void main_subtask_usb_state(void) {
    static uint64_t fsmstate_on_delay = 0;                          // Delay timer to be sure USB is actually operating before bringing up hardware
    uint8_t         fsmstate_now      = USB->DEVICE.FSMSTATUS.reg;  // Current state from hardware register

    if (fsmstate_now == USB_FSMSTATUS_FSMSTATE_SUSPEND_Val)  // If USB SUSPENDED
    {
        fsmstate_on_delay = 0;  // Clear ON delay timer

        if (g_usb_state != USB_FSMSTATUS_FSMSTATE_SUSPEND_Val)  // If previously not SUSPENDED
        {
            suspend_power_down();        // Run suspend routine
            g_usb_state = fsmstate_now;  // Save current USB state
        }
    } else if (fsmstate_now == USB_FSMSTATUS_FSMSTATE_SLEEP_Val)  // Else if USB SLEEPING
    {
        fsmstate_on_delay = 0;  // Clear ON delay timer

        if (g_usb_state != USB_FSMSTATUS_FSMSTATE_SLEEP_Val)  // If previously not SLEEPING
        {
            suspend_power_down();        // Run suspend routine
            g_usb_state = fsmstate_now;  // Save current USB state
        }
    } else if (fsmstate_now == USB_FSMSTATUS_FSMSTATE_ON_Val)  // Else if USB ON
    {
        if (g_usb_state != USB_FSMSTATUS_FSMSTATE_ON_Val)  // If previously not ON
        {
            if (fsmstate_on_delay == 0)  // If ON delay timer is cleared
            {
                fsmstate_on_delay = timer_read64() + 250;   // Set ON delay timer
            } else if (timer_read64() > fsmstate_on_delay)  // Else if ON delay timer is active and timed out
            {
                suspend_wakeup_init();       // Run wakeup routine
                g_usb_state = fsmstate_now;  // Save current USB state
            }
        }
    } else  // Else if USB is in a state not being tracked
    {
        fsmstate_on_delay = 0;  // Clear ON delay timer
    }
}