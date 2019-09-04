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
struct TYPE_4__ {int CIR; int /*<<< orphan*/  CR2; int /*<<< orphan*/  CFGR2; int /*<<< orphan*/  CFGR; int /*<<< orphan*/  CR; } ;
struct TYPE_3__ {int /*<<< orphan*/  CCR; } ;

/* Variables and functions */
 TYPE_2__* RCC ; 
 TYPE_1__* SCB ; 
 int /*<<< orphan*/  SCB_CCR_STKALIGN_Msk ; 

void SystemInit(void) {
    // Set HSION bit
    RCC->CR |= (uint32_t)0x00000001U;

    #if defined(STM32F051x8) || defined(STM32F058x8)
    // Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE and MCOSEL[2:0] bits
    RCC->CFGR &= (uint32_t)0xF8FFB80CU;
    #else
    // Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE, MCOSEL[2:0], MCOPRE[2:0] and PLLNODIV bits
    RCC->CFGR &= (uint32_t)0x08FFB80CU;
    #endif

    // Reset HSEON, CSSON and PLLON bits
    RCC->CR &= (uint32_t)0xFEF6FFFFU;

    // Reset HSEBYP bit
    RCC->CR &= (uint32_t)0xFFFBFFFFU;

    // Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits
    RCC->CFGR &= (uint32_t)0xFFC0FFFFU;

    // Reset PREDIV[3:0] bits
    RCC->CFGR2 &= (uint32_t)0xFFFFFFF0U;

    #if defined(STM32F072xB) || defined(STM32F078xx)
    // Reset USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW, USBSW and ADCSW bits
    RCC->CFGR3 &= (uint32_t)0xFFFCFE2CU;
    #elif defined(STM32F071xB)
    // Reset USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW and ADCSW bits
    RCC->CFGR3 &= (uint32_t)0xFFFFCEACU;
    #elif defined(STM32F091xC) || defined(STM32F098xx)
    // Reset USART3SW[1:0], USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW and ADCSW bits
    RCC->CFGR3 &= (uint32_t)0xFFF0FEACU;
    #elif defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F031x6) || defined(STM32F038xx) || defined(STM32F030xC)
    // Reset USART1SW[1:0], I2C1SW and ADCSW bits
    RCC->CFGR3 &= (uint32_t)0xFFFFFEECU;
    #elif defined(STM32F051x8) || defined(STM32F058xx)
    // Reset USART1SW[1:0], I2C1SW, CECSW and ADCSW bits
    RCC->CFGR3 &= (uint32_t)0xFFFFFEACU;
    #elif defined(STM32F042x6) || defined(STM32F048xx)
    // Reset USART1SW[1:0], I2C1SW, CECSW, USBSW and ADCSW bits
    RCC->CFGR3 &= (uint32_t)0xFFFFFE2CU;
    #elif defined(STM32F070x6) || defined(STM32F070xB)
    // Reset USART1SW[1:0], I2C1SW, USBSW and ADCSW bits
    RCC->CFGR3 &= (uint32_t)0xFFFFFE6CU;
    // Set default USB clock to PLLCLK, since there is no HSI48
    RCC->CFGR3 |= (uint32_t)0x00000080U;
    #else
    #warning "No target selected"
    #endif

    // Reset HSI14 bit
    RCC->CR2 &= (uint32_t)0xFFFFFFFEU;

    // Disable all interrupts
    RCC->CIR = 0x00000000U;

    // dpgeorge: enable 8-byte stack alignment for IRQ handlers, in accord with EABI
    SCB->CCR |= SCB_CCR_STKALIGN_Msk;
}