#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ActiveImg; int /*<<< orphan*/  PrevImg; } ;
typedef  TYPE_1__ sBootInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BOOTMGR_WAIT_SAFE_MODE_0_MS ; 
 int /*<<< orphan*/  BOOTMGR_WAIT_SAFE_MODE_1_BLINK_MS ; 
 int /*<<< orphan*/  BOOTMGR_WAIT_SAFE_MODE_1_MS ; 
 int /*<<< orphan*/  BOOTMGR_WAIT_SAFE_MODE_2_BLINK_MS ; 
 int /*<<< orphan*/  BOOTMGR_WAIT_SAFE_MODE_2_MS ; 
 int /*<<< orphan*/  BOOTMGR_WAIT_SAFE_MODE_3_BLINK_MS ; 
 int /*<<< orphan*/  BOOTMGR_WAIT_SAFE_MODE_3_MS ; 
 int /*<<< orphan*/  IMG_ACT_FACTORY ; 
 int /*<<< orphan*/  MAP_GPIOPinWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MICROPY_SYS_LED_PORT ; 
 int /*<<< orphan*/  MICROPY_SYS_LED_PORT_PIN ; 
 int /*<<< orphan*/  PRCMSetSpecialBit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRCM_SAFE_BOOT_BIT ; 
 int /*<<< orphan*/  mperror_deinit_sfe_pin () ; 
 scalar_t__ safe_boot_request_start (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_while_blinking (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wait_for_safe_boot (sBootInfo_t *psBootInfo) {
    if (safe_boot_request_start(BOOTMGR_WAIT_SAFE_MODE_0_MS)) {
        if (wait_while_blinking(BOOTMGR_WAIT_SAFE_MODE_1_MS, BOOTMGR_WAIT_SAFE_MODE_1_BLINK_MS, false)) {
            // go back one step in time
            psBootInfo->ActiveImg = psBootInfo->PrevImg;
            if (wait_while_blinking(BOOTMGR_WAIT_SAFE_MODE_2_MS, BOOTMGR_WAIT_SAFE_MODE_2_BLINK_MS, false)) {
                // go back directly to the factory image
                psBootInfo->ActiveImg = IMG_ACT_FACTORY;
                wait_while_blinking(BOOTMGR_WAIT_SAFE_MODE_3_MS, BOOTMGR_WAIT_SAFE_MODE_3_BLINK_MS, true);
            }
        }
        // turn off the system led
        MAP_GPIOPinWrite(MICROPY_SYS_LED_PORT, MICROPY_SYS_LED_PORT_PIN, 0);
        // request a safe boot to the application
        PRCMSetSpecialBit(PRCM_SAFE_BOOT_BIT);
    }
    // deinit the safe boot pin
    mperror_deinit_sfe_pin();
}