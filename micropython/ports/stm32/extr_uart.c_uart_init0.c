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
struct TYPE_3__ {int /*<<< orphan*/  Usart16ClockSelection; int /*<<< orphan*/  PeriphClockSelection; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RCC_PeriphCLKInitTypeDef ;

/* Variables and functions */
 scalar_t__ HAL_OK ; 
 scalar_t__ HAL_RCCEx_PeriphCLKConfig (TYPE_1__*) ; 
 int /*<<< orphan*/  RCC_PERIPHCLK_USART16 ; 
 int /*<<< orphan*/  RCC_PERIPHCLK_USART234578 ; 
 int /*<<< orphan*/  RCC_USART16CLKSOURCE_D2PCLK2 ; 
 int /*<<< orphan*/  RCC_USART234578CLKSOURCE_D2PCLK1 ; 
 int /*<<< orphan*/  __fatal_error (char*) ; 

void uart_init0(void) {
    #if defined(STM32H7)
    RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit = {0};
    // Configure USART1/6 clock source
    RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART16;
    RCC_PeriphClkInit.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
    if (HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit) != HAL_OK) {
        __fatal_error("HAL_RCCEx_PeriphCLKConfig");
    }

    // Configure USART2/3/4/5/7/8 clock source
    RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART234578;
    RCC_PeriphClkInit.Usart16ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit) != HAL_OK) {
        __fatal_error("HAL_RCCEx_PeriphCLKConfig");
    }
    #endif
}