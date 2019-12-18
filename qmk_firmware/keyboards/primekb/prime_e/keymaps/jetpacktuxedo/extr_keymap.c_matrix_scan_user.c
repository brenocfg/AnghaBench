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
 scalar_t__ BLINK_DURATION ; 
 scalar_t__ BLINK_TIMER ; 
 int CAPS ; 
 int /*<<< orphan*/  CAPS_LED_PIN ; 
 int /*<<< orphan*/  CAPS_LED_STATE ; 
 int /*<<< orphan*/  togg_indicator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void matrix_scan_user(void) {
    if (CAPS == 1) {
        // Blink the first led when capslock is active
        if (BLINK_TIMER >= BLINK_DURATION) {
            togg_indicator(&CAPS_LED_STATE, CAPS_LED_PIN);
            BLINK_TIMER = 0;
        }
        BLINK_TIMER++;
    }
}