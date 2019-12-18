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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_update_led_matrix (int /*<<< orphan*/ ) ; 
 TYPE_1__ led_matrix_config ; 
 int /*<<< orphan*/  led_matrix_set_value_noeeprom (int /*<<< orphan*/ ) ; 

void led_matrix_set_value(uint8_t val) {
    led_matrix_set_value_noeeprom(val);
    eeconfig_update_led_matrix(led_matrix_config.raw);
}