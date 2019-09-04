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
struct TYPE_2__ {int AHBxENR; } ;
typedef  int /*<<< orphan*/  GPIO_TypeDef ;

/* Variables and functions */
 int AHBxENR_GPIOAEN_Pos ; 
 int GPIOA_BASE ; 
 int GPIOB_BASE ; 
 TYPE_1__* RCC ; 

void mp_hal_gpio_clock_enable(GPIO_TypeDef *gpio) {
    #if defined(STM32L476xx) || defined(STM32L496xx)
    if (gpio == GPIOG) {
        // Port G pins 2 thru 15 are powered using VddIO2 on these MCUs.
        HAL_PWREx_EnableVddIO2();
    }
    #endif

    // This logic assumes that all the GPIOx_EN bits are adjacent and ordered in one register

    #if defined(STM32F0)
    #define AHBxENR AHBENR
    #define AHBxENR_GPIOAEN_Pos RCC_AHBENR_GPIOAEN_Pos
    #elif defined(STM32F4) || defined(STM32F7)
    #define AHBxENR AHB1ENR
    #define AHBxENR_GPIOAEN_Pos RCC_AHB1ENR_GPIOAEN_Pos
    #elif defined(STM32H7)
    #define AHBxENR AHB4ENR
    #define AHBxENR_GPIOAEN_Pos RCC_AHB4ENR_GPIOAEN_Pos
    #elif defined(STM32L4)
    #define AHBxENR AHB2ENR
    #define AHBxENR_GPIOAEN_Pos RCC_AHB2ENR_GPIOAEN_Pos
    #endif

    uint32_t gpio_idx = ((uint32_t)gpio - GPIOA_BASE) / (GPIOB_BASE - GPIOA_BASE);
    RCC->AHBxENR |= 1 << (AHBxENR_GPIOAEN_Pos + gpio_idx);
    volatile uint32_t tmp = RCC->AHBxENR; // Delay after enabling clock
    (void)tmp;
}