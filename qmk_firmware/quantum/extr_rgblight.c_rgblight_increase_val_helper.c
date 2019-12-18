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
struct TYPE_2__ {int /*<<< orphan*/  sat; int /*<<< orphan*/  hue; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGBLIGHT_VAL_STEP ; 
 int /*<<< orphan*/  qadd8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_sethsv_eeprom_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void rgblight_increase_val_helper(bool write_to_eeprom) {
    uint8_t val = qadd8(rgblight_config.val, RGBLIGHT_VAL_STEP);
    rgblight_sethsv_eeprom_helper(rgblight_config.hue, rgblight_config.sat, val, write_to_eeprom);
}