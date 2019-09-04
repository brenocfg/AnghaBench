#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int ACR; } ;
struct TYPE_3__ {int CR; int CFGR; scalar_t__ CFGR2; } ;

/* Variables and functions */
 TYPE_2__* FLASH ; 
 int HAL_RCC_GetHCLKFreq () ; 
 int /*<<< orphan*/  HAL_SYSTICK_CLKSourceConfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_SYSTICK_Config (int) ; 
 int HSE_VALUE ; 
 TYPE_1__* RCC ; 
 int RCC_CFGR_PLLMUL_Pos ; 
 int RCC_CFGR_PLLSRC_Pos ; 
 int RCC_CFGR_SWS_Pos ; 
 int const RCC_CFGR_SW_Pos ; 
 int RCC_CR_HSEON ; 
 int RCC_CR_HSERDY ; 
 int RCC_CR_PLLON ; 
 int RCC_CR_PLLRDY ; 
 int /*<<< orphan*/  SYSTICK_CLKSOURCE_HCLK ; 
 int /*<<< orphan*/  SystemCoreClockUpdate () ; 
 int /*<<< orphan*/  __HAL_RCC_PWR_CLK_ENABLE () ; 

void SystemClock_Config(void) {
    // Enable power control peripheral
    __HAL_RCC_PWR_CLK_ENABLE();

    // Set flash latency to 1 because SYSCLK > 24MHz
    FLASH->ACR = (FLASH->ACR & ~0x7) | 0x1;

    #if MICROPY_HW_CLK_USE_HSI48
    // Use the 48MHz internal oscillator

    RCC->CR2 |= RCC_CR2_HSI48ON;
    while ((RCC->CR2 & RCC_CR2_HSI48RDY) == 0) {
    }
    const uint32_t sysclk_src = 3;

    #else
    // Use HSE and the PLL to get a 48MHz SYSCLK

    #if MICROPY_HW_CLK_USE_BYPASS
    RCC->CR |= RCC_CR_HSEBYP;
    #endif
    RCC->CR |= RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY) == 0) {
        // Wait for HSE to be ready
    }
    RCC->CFGR = ((48000000 / HSE_VALUE) - 2) << RCC_CFGR_PLLMUL_Pos | 2 << RCC_CFGR_PLLSRC_Pos;
    RCC->CFGR2 = 0; // Input clock not divided
    RCC->CR |= RCC_CR_PLLON; // Turn PLL on
    while ((RCC->CR & RCC_CR_PLLRDY) == 0) {
        // Wait for PLL to lock
    }
    const uint32_t sysclk_src = 2;

    #endif

    // Select SYSCLK source
    RCC->CFGR |= sysclk_src << RCC_CFGR_SW_Pos;
    while (((RCC->CFGR >> RCC_CFGR_SWS_Pos) & 0x3) != sysclk_src) {
        // Wait for SYSCLK source to change
    }

    SystemCoreClockUpdate();

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}