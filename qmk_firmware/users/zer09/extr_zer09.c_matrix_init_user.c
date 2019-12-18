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
 int /*<<< orphan*/  eeprom_read_led_dim_lvl () ; 
 int /*<<< orphan*/  matrix_init_keymap () ; 

void matrix_init_user(void) {
  eeprom_read_led_dim_lvl();

  matrix_init_keymap();
}