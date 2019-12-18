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
typedef  int uint8_t ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 int RGBLIGHT_MODES ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_mode_eeprom_helper (int,int) ; 

void rgblight_step_helper(bool write_to_eeprom) {
    uint8_t mode = 0;
    mode         = rgblight_config.mode + 1;
    if (mode > RGBLIGHT_MODES) {
        mode = 1;
    }
    rgblight_mode_eeprom_helper(mode, write_to_eeprom);
}