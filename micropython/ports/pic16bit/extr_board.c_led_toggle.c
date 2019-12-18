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
 int RED_LED ; 
 int YELLOW_LED ; 

void led_toggle(int led) {
    switch (led) {
        case 1: RED_LED ^= 1; break;
        case 2: YELLOW_LED ^= 1; break;
        case 3: GREEN_LED ^= 1; break;
    }
}