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
struct TYPE_2__ {int /*<<< orphan*/  CTRL; } ;

/* Variables and functions */
 int HAL_RCC_GetHCLKFreq () ; 
 int /*<<< orphan*/  IRQ_PRI_SYSTICK ; 
 int /*<<< orphan*/  NVIC_SetPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSTICK_CLKSOURCE_HCLK ; 
 TYPE_1__* SysTick ; 
 int /*<<< orphan*/  SysTick_Config (int) ; 
 int /*<<< orphan*/  SysTick_IRQn ; 

__attribute__((used)) static inline void powerctrl_config_systick(void) {
    // Configure SYSTICK to run at 1kHz (1ms interval)
    SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
    SysTick_Config(HAL_RCC_GetHCLKFreq() / 1000);
    NVIC_SetPriority(SysTick_IRQn, IRQ_PRI_SYSTICK);
}