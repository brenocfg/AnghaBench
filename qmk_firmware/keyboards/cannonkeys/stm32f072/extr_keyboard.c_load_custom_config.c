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
 scalar_t__ EEPROM_CUSTOM_BACKLIGHT ; 
 int /*<<< orphan*/  eeprom_read_byte (int /*<<< orphan*/ *) ; 
 TYPE_1__ kb_backlight_config ; 

void load_custom_config(){
  kb_backlight_config.raw = eeprom_read_byte((uint8_t*)EEPROM_CUSTOM_BACKLIGHT);
}