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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BATTERY_PIN ; 
 float MAX_VOLTAGE ; 
 float MIN_VOLTAGE ; 
 int analogRead (int /*<<< orphan*/ ) ; 

uint8_t battery_level(void) {
    float voltage = analogRead(BATTERY_PIN) * 2 * 3.3 / 1024;
    if (voltage < MIN_VOLTAGE) return 0;
    if (voltage > MAX_VOLTAGE) return 255;
    return (voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE) * 255;
}