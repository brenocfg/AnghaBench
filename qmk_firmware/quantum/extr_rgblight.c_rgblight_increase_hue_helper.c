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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  val; int /*<<< orphan*/  sat; scalar_t__ hue; } ;

/* Variables and functions */
 scalar_t__ RGBLIGHT_HUE_STEP ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_sethsv_eeprom_helper (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void rgblight_increase_hue_helper(bool write_to_eeprom) {
    uint8_t hue = rgblight_config.hue + RGBLIGHT_HUE_STEP;
    rgblight_sethsv_eeprom_helper(hue, rgblight_config.sat, rgblight_config.val, write_to_eeprom);
}