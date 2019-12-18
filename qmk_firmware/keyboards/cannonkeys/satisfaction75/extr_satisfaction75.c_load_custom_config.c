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
struct TYPE_2__ {void* raw; } ;

/* Variables and functions */
 scalar_t__ DYNAMIC_KEYMAP_CUSTOM_BACKLIGHT ; 
 scalar_t__ DYNAMIC_KEYMAP_DEFAULT_OLED ; 
 scalar_t__ DYNAMIC_KEYMAP_ENABLED_ENCODER_MODES ; 
 void* eeprom_read_byte (int /*<<< orphan*/ *) ; 
 void* enabled_encoder_modes ; 
 TYPE_1__ kb_backlight_config ; 
 void* oled_mode ; 

void load_custom_config(){
  kb_backlight_config.raw = eeprom_read_byte((uint8_t*)DYNAMIC_KEYMAP_CUSTOM_BACKLIGHT);
#ifdef DYNAMIC_KEYMAP_ENABLE
  oled_mode = eeprom_read_byte((uint8_t*)DYNAMIC_KEYMAP_DEFAULT_OLED);
  enabled_encoder_modes = eeprom_read_byte((uint8_t*)DYNAMIC_KEYMAP_ENABLED_ENCODER_MODES);
#endif
}