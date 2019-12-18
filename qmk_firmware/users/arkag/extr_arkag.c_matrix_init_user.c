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
 int /*<<< orphan*/  EECONFIG_USERSPACE ; 
 int /*<<< orphan*/  current_os ; 
 int /*<<< orphan*/  eeprom_read_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_os (int /*<<< orphan*/ ,int) ; 

void matrix_init_user(void) {
  current_os = eeprom_read_byte(EECONFIG_USERSPACE);
  set_os(current_os, false);
}