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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  FEE_DENSITY_BYTES ; 
 int /*<<< orphan*/  FLASH_Unlock () ; 

uint16_t EEPROM_Init(void) {
    // unlock flash
    FLASH_Unlock();

    // Clear Flags
    // FLASH_ClearFlag(FLASH_SR_EOP|FLASH_SR_PGERR|FLASH_SR_WRPERR);

    return FEE_DENSITY_BYTES;
}