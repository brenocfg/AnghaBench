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
 int FLED_VAL_STEP ; 
 int /*<<< orphan*/  eeprom_update_conf () ; 
 int fled_val ; 
 int /*<<< orphan*/  rgblight_set () ; 

void fled_val_increase(void)
{
    // Increase val by FLED_VAL_STEP, handling the upper edge case
    if (fled_val + FLED_VAL_STEP > 255)
        fled_val = 255;
    else
        fled_val += FLED_VAL_STEP;
    
    // Update stored config
    eeprom_update_conf();
    rgblight_set();
}