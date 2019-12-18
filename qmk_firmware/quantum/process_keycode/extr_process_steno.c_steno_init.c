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
 int /*<<< orphan*/  EECONFIG_STENOMODE ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  eeprom_read_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode ; 

void steno_init() {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    mode = eeprom_read_byte(EECONFIG_STENOMODE);
}