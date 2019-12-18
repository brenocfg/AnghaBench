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
 scalar_t__ DYNAMIC_KEYMAP_CUSTOM_BACKLIGHT ; 
 int /*<<< orphan*/  eeprom_update_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ kb_backlight_config ; 

void save_backlight_config_to_eeprom(){
  eeprom_update_byte((uint8_t*)DYNAMIC_KEYMAP_CUSTOM_BACKLIGHT, kb_backlight_config.raw);
}