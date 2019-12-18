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
 int GREEN_LED ; 
 int LED_OFF ; 
 int LED_ON ; 
 int RED_LED ; 
 int YELLOW_LED ; 

void led_state(int led, int state) {
    int val = state ? LED_ON : LED_OFF;
    switch (led) {
        case 1: RED_LED = val; break;
        case 2: YELLOW_LED = val; break;
        case 3: GREEN_LED = val; break;
    }
}