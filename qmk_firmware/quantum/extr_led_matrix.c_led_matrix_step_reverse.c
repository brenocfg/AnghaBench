#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mode; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int LED_MATRIX_EFFECT_MAX ; 
 int /*<<< orphan*/  eeconfig_update_led_matrix (int /*<<< orphan*/ ) ; 
 TYPE_1__ led_matrix_config ; 

void led_matrix_step_reverse(void) {
    led_matrix_config.mode--;
    if (led_matrix_config.mode < 1) {
        led_matrix_config.mode = LED_MATRIX_EFFECT_MAX - 1;
    }
    eeconfig_update_led_matrix(led_matrix_config.raw);
}