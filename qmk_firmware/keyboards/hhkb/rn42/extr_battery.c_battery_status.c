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
typedef  int /*<<< orphan*/  battery_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHARGING ; 
 int /*<<< orphan*/  DISCHARGING ; 
 int /*<<< orphan*/  FULL_CHARGED ; 
 int /*<<< orphan*/  LOW_VOLTAGE ; 
 int USBSTA ; 
 int VBUS ; 
 scalar_t__ battery_charging () ; 
 scalar_t__ low_voltage () ; 

battery_status_t battery_status(void)
{
    if (USBSTA&(1<<VBUS)) {
        /* powered */
        return battery_charging() ? CHARGING : FULL_CHARGED;
    } else {
        /* not powered */
        return low_voltage() ? LOW_VOLTAGE : DISCHARGING;
    }
}