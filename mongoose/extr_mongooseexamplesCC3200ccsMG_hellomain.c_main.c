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
 int /*<<< orphan*/  FAULT_SYSTICK ; 
 int /*<<< orphan*/  GPIOA1_BASE ; 
 int /*<<< orphan*/  GPIO_DIR_MODE_OUT ; 
 int /*<<< orphan*/  GPIO_IF_LedConfigure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_IF_LedOn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED1 ; 
 int /*<<< orphan*/  LL_ERROR ; 
 int /*<<< orphan*/  LL_INFO ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAP_GPIODirModeSet (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_IntEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_IntMasterEnable () ; 
 int /*<<< orphan*/  MAP_IntVTableBaseSet (unsigned long) ; 
 int /*<<< orphan*/  MAP_PRCMPeripheralClkEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_PinTypeGPIO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MCU_RED_LED_GPIO ; 
 int /*<<< orphan*/  MGOS_TASK_PRIORITY ; 
 int /*<<< orphan*/  MG_TASK_STACK_SIZE ; 
 int /*<<< orphan*/  PIN_64 ; 
 int /*<<< orphan*/  PIN_MODE_0 ; 
 int /*<<< orphan*/  PRCMCC3200MCUInit () ; 
 int /*<<< orphan*/  PRCM_GPIOA1 ; 
 int /*<<< orphan*/  PRCM_RUN_MODE_CLK ; 
 scalar_t__ VStartSimpleLinkSpawnTask (int) ; 
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  cs_log_set_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_log_set_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_pfnVectors ; 
 int /*<<< orphan*/  mg_init ; 
 int /*<<< orphan*/  mg_start_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_start () ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int main(void) {
#ifndef USE_TIRTOS
  MAP_IntVTableBaseSet((unsigned long) &g_pfnVectors[0]);
#endif
  MAP_IntEnable(FAULT_SYSTICK);
  MAP_IntMasterEnable();
  PRCMCC3200MCUInit();

  setvbuf(stdout, NULL, _IOLBF, 0);
  setvbuf(stderr, NULL, _IOLBF, 0);
  cs_log_set_level(LL_INFO);
  cs_log_set_file(stdout);

  LOG(LL_INFO, ("Hello, world!"));

  /* Set up the red LED. Note that amber and green cannot be used as they share
   * pins with I2C. */
  MAP_PRCMPeripheralClkEnable(PRCM_GPIOA1, PRCM_RUN_MODE_CLK);
  MAP_PinTypeGPIO(PIN_64, PIN_MODE_0, false);
  MAP_GPIODirModeSet(GPIOA1_BASE, 0x2, GPIO_DIR_MODE_OUT);
  GPIO_IF_LedConfigure(LED1);
  GPIO_IF_LedOn(MCU_RED_LED_GPIO);

  if (VStartSimpleLinkSpawnTask(8) != 0) {
    LOG(LL_ERROR, ("Failed to create SL task"));
  }

  if (!mg_start_task(MGOS_TASK_PRIORITY, MG_TASK_STACK_SIZE, mg_init)) {
    LOG(LL_ERROR, ("Failed to create MG task"));
  }

  osi_start();

  return 0;
}