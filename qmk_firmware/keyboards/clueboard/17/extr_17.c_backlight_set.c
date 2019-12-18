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
 int OCR4A ; 
 int TC4H ; 
 int pwm_level ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

void backlight_set(uint8_t level) {
    // Determine the PWM level
    switch (level)
    {
        case 0:
            // 33%
            pwm_level = 0x54;
            break;
        case 1:
            // 66%
            pwm_level = 0xA8;
            break;
        case 2:
            // 100%
            pwm_level = 0xFF;
            break;
        case 3:
            // 0%
            pwm_level = 0x00;
            break;
        default:
            xprintf("Unknown level: %d\n", level);
    }

    // Write the PWM level to the timer
    TC4H = pwm_level >> 8;
    OCR4A = 0xFF & pwm_level;
}