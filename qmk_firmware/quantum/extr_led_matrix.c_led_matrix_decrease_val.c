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
struct TYPE_2__ {int /*<<< orphan*/  raw; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_MATRIX_MAXIMUM_BRIGHTNESS ; 
 int /*<<< orphan*/  decrement (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeconfig_update_led_matrix (int /*<<< orphan*/ ) ; 
 TYPE_1__ led_matrix_config ; 

void led_matrix_decrease_val(void) {
    led_matrix_config.val = decrement(led_matrix_config.val, 8, 0, LED_MATRIX_MAXIMUM_BRIGHTNESS);
    eeconfig_update_led_matrix(led_matrix_config.raw);
}