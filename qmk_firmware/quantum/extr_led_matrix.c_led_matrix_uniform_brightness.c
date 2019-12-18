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
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 int BACKLIGHT_LEVELS ; 
 int LED_MATRIX_MAXIMUM_BRIGHTNESS ; 
 TYPE_1__ led_matrix_config ; 
 int /*<<< orphan*/  led_matrix_set_index_value_all (int) ; 

void led_matrix_uniform_brightness(void) { led_matrix_set_index_value_all(LED_MATRIX_MAXIMUM_BRIGHTNESS / BACKLIGHT_LEVELS * led_matrix_config.val); }