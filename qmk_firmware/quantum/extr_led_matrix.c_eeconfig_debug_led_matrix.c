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
struct TYPE_2__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  val; int /*<<< orphan*/  mode; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (char*,...) ; 
 TYPE_1__ led_matrix_config ; 

void eeconfig_debug_led_matrix(void) {
    dprintf("led_matrix_config eeprom\n");
    dprintf("led_matrix_config.enable = %d\n", led_matrix_config.enable);
    dprintf("led_matrix_config.mode = %d\n", led_matrix_config.mode);
    dprintf("led_matrix_config.val = %d\n", led_matrix_config.val);
    dprintf("led_matrix_config.speed = %d\n", led_matrix_config.speed);
}