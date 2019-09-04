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
struct TYPE_4__ {int ACR; } ;
struct TYPE_3__ {int CR; int CFGR; int PLLCFGR; } ;

/* Variables and functions */
 TYPE_2__* FLASH ; 
 int FLASH_ACR_DCEN ; 
 int FLASH_ACR_ICEN ; 
 int FLASH_ACR_LATENCY_5WS ; 
 TYPE_1__* RCC ; 
 int RCC_CFGR_HPRE_DIV1 ; 
 int RCC_CFGR_PPRE1_DIV4 ; 
 int RCC_CFGR_PPRE2_DIV2 ; 
 int RCC_CFGR_SWS ; 
 int RCC_CFGR_SWS_PLL ; 
 int RCC_CFGR_SW_PLL ; 
 int RCC_CR_HSEON ; 
 int RCC_CR_HSERDY ; 
 int RCC_CR_PLLON ; 
 int RCC_CR_PLLRDY ; 
 int RCC_PLLCFGR_PLLM_3 ; 
 int RCC_PLLCFGR_PLLN_6 ; 
 int RCC_PLLCFGR_PLLN_7 ; 
 int RCC_PLLCFGR_PLLQ_2 ; 
 int RCC_PLLCFGR_PLLSRC_HSE ; 

void clock_init() {
  // enable external oscillator
  RCC->CR |= RCC_CR_HSEON;
  while ((RCC->CR & RCC_CR_HSERDY) == 0);

  // divide shit
  RCC->CFGR = RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE2_DIV2 | RCC_CFGR_PPRE1_DIV4;
  #ifdef PANDA
    RCC->PLLCFGR = RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLM_3 |
                   RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLSRC_HSE;
  #else
    #ifdef PEDAL
      // comma pedal has a 16mhz crystal
      RCC->PLLCFGR = RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLM_3 |
                     RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLSRC_HSE;
    #else
      // NEO board has a 8mhz crystal
      RCC->PLLCFGR = RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLM_3 |
                     RCC_PLLCFGR_PLLN_7 | RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLSRC_HSE;
    #endif
  #endif

  // start PLL
  RCC->CR |= RCC_CR_PLLON;
  while ((RCC->CR & RCC_CR_PLLRDY) == 0);

  // Configure Flash prefetch, Instruction cache, Data cache and wait state
  // *** without this, it breaks ***
  FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

  // switch to PLL
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // *** running on PLL ***
}