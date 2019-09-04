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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int CFGR; int /*<<< orphan*/  CR; int /*<<< orphan*/  PLLCFGR; } ;
struct TYPE_3__ {int VTOR; int /*<<< orphan*/  CCR; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RCC_CR_1ST ; 
 int /*<<< orphan*/  CONFIG_RCC_CR_2ND ; 
 int /*<<< orphan*/  CONFIG_RCC_PLLCFGR ; 
 int FLASH_BASE ; 
 TYPE_2__* RCC ; 
 TYPE_1__* SCB ; 
 int /*<<< orphan*/  SCB_CCR_STKALIGN_Msk ; 
 int VECT_TAB_OFFSET ; 

void SystemInit(void)
{
  /* FPU settings ------------------------------------------------------------*/
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
  #endif
  /* Reset the RCC clock configuration to the default reset state ------------*/

  /* Set configured startup clk source */
  RCC->CR |= CONFIG_RCC_CR_1ST;

  /* Reset CFGR register */
  RCC->CFGR = 0x00000000;

  /* Reset HSxON, CSSON and PLLON bits */
  RCC->CR &= ~ CONFIG_RCC_CR_2ND;

  /* Reset PLLCFGR register */
  RCC->PLLCFGR = CONFIG_RCC_PLLCFGR;

  #if defined(STM32H7)
  /* Reset D1CFGR register */
  RCC->D1CFGR = 0x00000000;

  /* Reset D2CFGR register */
  RCC->D2CFGR = 0x00000000;

  /* Reset D3CFGR register */
  RCC->D3CFGR = 0x00000000;

  /* Reset PLLCKSELR register */
  RCC->PLLCKSELR = 0x00000000;

  /* Reset PLL1DIVR register */
  RCC->PLL1DIVR = 0x00000000;

  /* Reset PLL1FRACR register */
  RCC->PLL1FRACR = 0x00000000;

  /* Reset PLL2DIVR register */
  RCC->PLL2DIVR = 0x00000000;

  /* Reset PLL2FRACR register */
  RCC->PLL2FRACR = 0x00000000;

  /* Reset PLL3DIVR register */
  RCC->PLL3DIVR = 0x00000000;

  /* Reset PLL3FRACR register */
  RCC->PLL3FRACR = 0x00000000;
  #endif

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Disable all interrupts */
  #if defined(STM32F4) || defined(STM32F7)
  RCC->CIR = 0x00000000;
  #elif defined(STM32L4) || defined(STM32H7)
  RCC->CIER = 0x00000000;
  #endif

  #if defined(STM32H7)
  /* Change the switch matrix read issuing capability to 1 for the AXI SRAM target (Target 7) */
  *((__IO uint32_t*)0x51008108) = 0x00000001;
  #endif

  /* Configure the Vector Table location add offset address ------------------*/
#ifdef MICROPY_HW_VTOR
  SCB->VTOR = MICROPY_HW_VTOR;
#else
#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM1_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
#endif
#endif

  /* dpgeorge: enable 8-byte stack alignment for IRQ handlers, in accord with EABI */
  SCB->CCR |= SCB_CCR_STKALIGN_Msk;
}