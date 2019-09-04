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
struct TYPE_2__ {int CFGR; int CFGR2; } ;

/* Variables and functions */
 int* AHBPrescTable ; 
 int HSE_VALUE ; 
 int HSI48_VALUE ; 
 int HSI_VALUE ; 
 TYPE_1__* RCC ; 
 int RCC_CFGR2_PREDIV ; 
 int RCC_CFGR_HPRE ; 
 int RCC_CFGR_PLLMUL ; 
 int RCC_CFGR_PLLSRC ; 
 int RCC_CFGR_PLLSRC_HSE_PREDIV ; 
 int RCC_CFGR_SWS ; 
#define  RCC_CFGR_SWS_HSE 131 
#define  RCC_CFGR_SWS_HSI 130 
#define  RCC_CFGR_SWS_HSI48 129 
#define  RCC_CFGR_SWS_PLL 128 
 int SystemCoreClock ; 

void SystemCoreClockUpdate(void) {
    // Get SYSCLK source
    uint32_t tmp = RCC->CFGR & RCC_CFGR_SWS;

    switch (tmp) {
        case RCC_CFGR_SWS_HSI:
            SystemCoreClock = HSI_VALUE;
            break;
        case RCC_CFGR_SWS_HSE:
            SystemCoreClock = HSE_VALUE;
            break;
        case RCC_CFGR_SWS_PLL: {
            /* Get PLL clock source and multiplication factor */
            uint32_t pllmull = RCC->CFGR & RCC_CFGR_PLLMUL;
            uint32_t pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
            pllmull = (pllmull >> 18) + 2;
            uint32_t predivfactor = (RCC->CFGR2 & RCC_CFGR2_PREDIV) + 1;

            if (pllsource == RCC_CFGR_PLLSRC_HSE_PREDIV) {
                /* HSE used as PLL clock source : SystemCoreClock = HSE/PREDIV * PLLMUL */
                SystemCoreClock = (HSE_VALUE/predivfactor) * pllmull;
            #if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F072xB) \
                || defined(STM32F078xx) || defined(STM32F091xC) || defined(STM32F098xx)
            } else if (pllsource == RCC_CFGR_PLLSRC_HSI48_PREDIV) {
                /* HSI48 used as PLL clock source : SystemCoreClock = HSI48/PREDIV * PLLMUL */
                SystemCoreClock = (HSI48_VALUE/predivfactor) * pllmull;
            #endif
            } else {
                #if defined(STM32F042x6) || defined(STM32F048xx)  || defined(STM32F070x6) \
                    || defined(STM32F078xx) || defined(STM32F071xB)  || defined(STM32F072xB) \
                    || defined(STM32F070xB) || defined(STM32F091xC) || defined(STM32F098xx)  || defined(STM32F030xC)
                /* HSI used as PLL clock source : SystemCoreClock = HSI/PREDIV * PLLMUL */
                SystemCoreClock = (HSI_VALUE / predivfactor) * pllmull;
                #else
                /* HSI used as PLL clock source : SystemCoreClock = HSI/2 * PLLMUL */
                SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
                #endif
            }
            break;
        }
        case RCC_CFGR_SWS_HSI48:
            SystemCoreClock = HSI48_VALUE;
            break;
        default:
            SystemCoreClock = HSI_VALUE;
            break;
    }

    // Compute HCLK clock frequency
    tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
    SystemCoreClock >>= tmp;
}