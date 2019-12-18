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
 int /*<<< orphan*/  EECONFIG_VELOCIKEY ; 
 int /*<<< orphan*/  eeprom_update_byte (int /*<<< orphan*/ ,int) ; 
 scalar_t__ velocikey_enabled () ; 

void velocikey_toggle(void) {
    if (velocikey_enabled())
        eeprom_update_byte(EECONFIG_VELOCIKEY, 0);
    else
        eeprom_update_byte(EECONFIG_VELOCIKEY, 1);
}