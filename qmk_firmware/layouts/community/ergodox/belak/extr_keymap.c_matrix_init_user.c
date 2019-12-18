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
 int /*<<< orphan*/  EECONFIG_BELAK ; 
 scalar_t__ EECONFIG_BELAK_MAGIC ; 
 int /*<<< orphan*/  EECONFIG_BELAK_SWAP_GUI_CTRL ; 
 int /*<<< orphan*/  SWPH ; 
 scalar_t__ eeprom_read_byte (int /*<<< orphan*/ ) ; 
 scalar_t__ eeprom_read_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeprom_update_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeprom_update_word (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int swap_gui_ctrl ; 

void matrix_init_user(void) {
    // If our magic word wasn't set properly, we need to zero out the settings.
    if (eeprom_read_word(EECONFIG_BELAK) != EECONFIG_BELAK_MAGIC) {
        eeprom_update_word(EECONFIG_BELAK, EECONFIG_BELAK_MAGIC);
        eeprom_update_byte(EECONFIG_BELAK_SWAP_GUI_CTRL, 0);
    }

    if (eeprom_read_byte(EECONFIG_BELAK_SWAP_GUI_CTRL)) {
        layer_on(SWPH);
        swap_gui_ctrl = 1;
    }
}