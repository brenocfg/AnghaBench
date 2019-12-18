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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ BATTERY_VOLTAGE_LOW_LIMIT ; 
 scalar_t__ BATTERY_VOLTAGE_LOW_RECOVERY ; 
 scalar_t__ battery_voltage () ; 

__attribute__((used)) static bool low_voltage(void) {
    static bool low = false;
    uint16_t v = battery_voltage();
    if (v < BATTERY_VOLTAGE_LOW_LIMIT) {
        low = true;
    } else if (v > BATTERY_VOLTAGE_LOW_RECOVERY) {
        low = false;
    }
    return low;
}