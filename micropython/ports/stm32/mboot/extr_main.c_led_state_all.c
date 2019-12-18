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
 int /*<<< orphan*/  LED0 ; 
 int /*<<< orphan*/  LED1 ; 
 int /*<<< orphan*/  LED2 ; 
 int /*<<< orphan*/  LED3 ; 
 int /*<<< orphan*/  led_state (int /*<<< orphan*/ ,unsigned int) ; 

void led_state_all(unsigned int mask) {
    led_state(LED0, mask & 1);
    led_state(LED1, mask & 2);
    #ifdef LED2
    led_state(LED2, mask & 4);
    #endif
    #ifdef LED3
    led_state(LED3, mask & 8);
    #endif
}