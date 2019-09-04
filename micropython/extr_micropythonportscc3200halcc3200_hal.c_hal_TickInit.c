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
typedef  int /*<<< orphan*/  HWREG ;

/* Variables and functions */
 int /*<<< orphan*/  FAULT_SYSTICK ; 
 int HAL_FCPU_HZ ; 
 int /*<<< orphan*/  HAL_IncrementTick ; 
 int HAL_SYSTICK_PERIOD_US ; 
 scalar_t__ HAL_tickCount ; 
 int /*<<< orphan*/  MAP_IntEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_SysTickEnable () ; 
 int /*<<< orphan*/  MAP_SysTickIntEnable () ; 
 int /*<<< orphan*/  MAP_SysTickIntRegister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_SysTickPeriodSet (int) ; 

__attribute__((used)) static void hal_TickInit (void) {
    HAL_tickCount = 0;
    MAP_SysTickIntRegister(HAL_IncrementTick);
    MAP_IntEnable(FAULT_SYSTICK);
    MAP_SysTickIntEnable();
    MAP_SysTickPeriodSet(HAL_FCPU_HZ / HAL_SYSTICK_PERIOD_US);
    // Force a reload of the SysTick counter register
    HWREG(NVIC_ST_CURRENT) = 0;
    MAP_SysTickEnable();
}