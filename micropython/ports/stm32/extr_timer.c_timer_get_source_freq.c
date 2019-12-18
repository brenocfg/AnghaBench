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
typedef  int uint32_t ;
struct TYPE_2__ {int CFGR; int D2CFGR; } ;

/* Variables and functions */
 int HAL_RCC_GetPCLK1Freq () ; 
 int HAL_RCC_GetPCLK2Freq () ; 
 TYPE_1__* RCC ; 
 int RCC_CFGR_PPRE ; 
 int RCC_CFGR_PPRE1 ; 
 int RCC_CFGR_PPRE2 ; 
 int RCC_D2CFGR_D2PPRE1 ; 
 int RCC_D2CFGR_D2PPRE2 ; 

uint32_t timer_get_source_freq(uint32_t tim_id) {
    uint32_t source, clk_div;
    if (tim_id == 1 || (8 <= tim_id && tim_id <= 11)) {
        // TIM{1,8,9,10,11} are on APB2
        #if defined(STM32F0)
        source = HAL_RCC_GetPCLK1Freq();
        clk_div = RCC->CFGR & RCC_CFGR_PPRE;
        #elif defined(STM32H7)
        source = HAL_RCC_GetPCLK2Freq();
        clk_div = RCC->D2CFGR & RCC_D2CFGR_D2PPRE2;
        #else
        source = HAL_RCC_GetPCLK2Freq();
        clk_div = RCC->CFGR & RCC_CFGR_PPRE2;
        #endif
    } else {
        // TIM{2,3,4,5,6,7,12,13,14} are on APB1
        source = HAL_RCC_GetPCLK1Freq();
        #if defined(STM32F0)
        clk_div = RCC->CFGR & RCC_CFGR_PPRE;
        #elif defined(STM32H7)
        clk_div = RCC->D2CFGR & RCC_D2CFGR_D2PPRE1;
        #else
        clk_div = RCC->CFGR & RCC_CFGR_PPRE1;
        #endif
    }
    if (clk_div != 0) {
        // APB prescaler for this timer is > 1
        source *= 2;
    }
    return source;
}