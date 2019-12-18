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
typedef  int /*<<< orphan*/  backlight_config ;

/* Variables and functions */
 scalar_t__ RGB_BACKLIGHT_CONFIG_EEPROM_ADDR ; 
 int /*<<< orphan*/  eeprom_update_block (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  g_config ; 

void backlight_config_save(void)
{
    eeprom_update_block( &g_config, ((void*)RGB_BACKLIGHT_CONFIG_EEPROM_ADDR), sizeof(backlight_config) );
}