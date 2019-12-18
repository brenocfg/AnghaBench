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
typedef  int /*<<< orphan*/  steno_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EECONFIG_STENOMODE ; 
 int /*<<< orphan*/  eeprom_update_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode ; 
 int /*<<< orphan*/  steno_clear_state () ; 

void steno_set_mode(steno_mode_t new_mode) {
    steno_clear_state();
    mode = new_mode;
    eeprom_update_byte(EECONFIG_STENOMODE, mode);
}