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
 void* GREEN_LED ; 
 scalar_t__ GREEN_LED_TRIS ; 
 void* LED_OFF ; 
 void* RED_LED ; 
 scalar_t__ RED_LED_TRIS ; 
 void* YELLOW_LED ; 
 scalar_t__ YELLOW_LED_TRIS ; 

void led_init(void) {
    // set led GPIO as outputs
    RED_LED_TRIS = 0;
    YELLOW_LED_TRIS = 0;
    GREEN_LED_TRIS = 0;

    // turn off the LEDs
    RED_LED = LED_OFF;
    YELLOW_LED = LED_OFF;
    GREEN_LED = LED_OFF;
}