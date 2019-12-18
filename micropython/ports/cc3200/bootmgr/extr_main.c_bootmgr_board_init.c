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
 int /*<<< orphan*/  CRYPTOHASH_Init () ; 
 int /*<<< orphan*/  FAULT_SYSTICK ; 
 int /*<<< orphan*/  MAP_IntEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_IntMasterEnable () ; 
 int /*<<< orphan*/  MAP_IntVTableBaseSet (unsigned long) ; 
 int /*<<< orphan*/  PRCMCC3200MCUInit () ; 
 int /*<<< orphan*/  PRCMClearSpecialBit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRCM_FIRST_BOOT_BIT ; 
 int /*<<< orphan*/  PRCM_SAFE_BOOT_BIT ; 
 int /*<<< orphan*/  antenna_init0 () ; 
 int /*<<< orphan*/ * g_pfnVectors ; 
 int /*<<< orphan*/  mperror_bootloader_check_reset_cause () ; 
 int /*<<< orphan*/  mperror_init0 () ; 

__attribute__((used)) static void bootmgr_board_init(void) {
    // set the vector table base
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);

    // enable processor interrupts
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    // mandatory MCU initialization
    PRCMCC3200MCUInit();

    // clear all the special bits, since we can't trust their content after reset
    // except for the WDT reset one!!
    PRCMClearSpecialBit(PRCM_SAFE_BOOT_BIT);
    PRCMClearSpecialBit(PRCM_FIRST_BOOT_BIT);

    // check the reset after clearing the special bits
    mperror_bootloader_check_reset_cause();

#if MICROPY_HW_ANTENNA_DIVERSITY
    // configure the antenna selection pins
    antenna_init0();
#endif

    // enable the data hashing engine
    CRYPTOHASH_Init();

    // init the system led and the system switch
    mperror_init0();
}