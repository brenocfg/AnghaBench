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
 int /*<<< orphan*/  PYB_LED_BUILTIN ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  led_state (int /*<<< orphan*/ ,int) ; 

void flash_error(int n) {
    for (int i = 0; i < n; i++) {
        led_state(PYB_LED_BUILTIN, 1);
        delay(250);
        led_state(PYB_LED_BUILTIN, 0);
        delay(250);
    }
}