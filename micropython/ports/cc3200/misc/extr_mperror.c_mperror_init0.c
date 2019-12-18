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
typedef  int /*<<< orphan*/  pin_obj_t ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_DIR_MODE_IN ; 
 int /*<<< orphan*/  GPIO_DIR_MODE_OUT ; 
 int /*<<< orphan*/  MAP_GPIODirModeSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_PRCMPeripheralClkEnable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAP_PinConfigSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_PinTypeGPIO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MICROPY_SAFE_BOOT_PIN_NUM ; 
 int /*<<< orphan*/  MICROPY_SAFE_BOOT_PORT ; 
 int /*<<< orphan*/  MICROPY_SAFE_BOOT_PORT_PIN ; 
 int /*<<< orphan*/  MICROPY_SAFE_BOOT_PRCM ; 
 int /*<<< orphan*/  MICROPY_SYS_LED_GPIO ; 
 int /*<<< orphan*/  MICROPY_SYS_LED_PIN_NUM ; 
 int /*<<< orphan*/  MICROPY_SYS_LED_PORT ; 
 int /*<<< orphan*/  MICROPY_SYS_LED_PORT_PIN ; 
 int /*<<< orphan*/  MICROPY_SYS_LED_PRCM ; 
 int /*<<< orphan*/  PIN_MODE_0 ; 
 int /*<<< orphan*/  PIN_STRENGTH_4MA ; 
 int /*<<< orphan*/  PIN_STRENGTH_6MA ; 
 int /*<<< orphan*/  PIN_TYPE_STD ; 
 int /*<<< orphan*/  PIN_TYPE_STD_PD ; 
 int PRCM_RUN_MODE_CLK ; 
 int PRCM_SLP_MODE_CLK ; 
 TYPE_1__ mperror_heart_beat ; 
 int /*<<< orphan*/  mperror_heartbeat_switch_off () ; 
 int /*<<< orphan*/  pin_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mperror_init0 (void) {
#ifdef BOOTLOADER
    // enable the system led and the safe boot pin peripheral clocks
    MAP_PRCMPeripheralClkEnable(MICROPY_SYS_LED_PRCM, PRCM_RUN_MODE_CLK | PRCM_SLP_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(MICROPY_SAFE_BOOT_PRCM, PRCM_RUN_MODE_CLK | PRCM_SLP_MODE_CLK);
    // configure the safe boot pin
    MAP_PinTypeGPIO(MICROPY_SAFE_BOOT_PIN_NUM, PIN_MODE_0, false);
    MAP_PinConfigSet(MICROPY_SAFE_BOOT_PIN_NUM, PIN_STRENGTH_4MA, PIN_TYPE_STD_PD);
    MAP_GPIODirModeSet(MICROPY_SAFE_BOOT_PORT, MICROPY_SAFE_BOOT_PORT_PIN, GPIO_DIR_MODE_IN);
    // configure the bld
    MAP_PinTypeGPIO(MICROPY_SYS_LED_PIN_NUM, PIN_MODE_0, false);
    MAP_PinConfigSet(MICROPY_SYS_LED_PIN_NUM, PIN_STRENGTH_6MA, PIN_TYPE_STD);
    MAP_GPIODirModeSet(MICROPY_SYS_LED_PORT, MICROPY_SYS_LED_PORT_PIN, GPIO_DIR_MODE_OUT);
#else
    // configure the system led
    pin_config ((pin_obj_t *)&MICROPY_SYS_LED_GPIO, PIN_MODE_0, GPIO_DIR_MODE_OUT, PIN_TYPE_STD, 0, PIN_STRENGTH_6MA);
#endif
    mperror_heart_beat.enabled = true;
    mperror_heartbeat_switch_off();
}