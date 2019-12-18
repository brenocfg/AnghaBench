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
struct TYPE_2__ {int enable; int val; int /*<<< orphan*/  raw; scalar_t__ speed; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_MATRIX_UNIFORM_BRIGHTNESS ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  eeconfig_update_led_matrix (int /*<<< orphan*/ ) ; 
 TYPE_1__ led_matrix_config ; 

void eeconfig_update_led_matrix_default(void) {
    dprintf("eeconfig_update_led_matrix_default\n");
    led_matrix_config.enable = 1;
    led_matrix_config.mode   = LED_MATRIX_UNIFORM_BRIGHTNESS;
    led_matrix_config.val    = 128;
    led_matrix_config.speed  = 0;
    eeconfig_update_led_matrix(led_matrix_config.raw);
}