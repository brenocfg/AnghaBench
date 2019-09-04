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
typedef  int mp_hal_pin_obj_t ;
struct TYPE_4__ {int AHBxENR; } ;
struct TYPE_3__ {int MODER; int OTYPER; int OSPEEDR; int PUPDR; int* AFR; } ;
typedef  TYPE_1__ GPIO_TypeDef ;

/* Variables and functions */
 int AHBxENR_GPIOAEN_Pos ; 
 uintptr_t GPIOA_BASE ; 
 uintptr_t GPIOB_BASE ; 
 TYPE_2__* RCC ; 

void mp_hal_pin_config(mp_hal_pin_obj_t port_pin, uint32_t mode, uint32_t pull, uint32_t alt) {
    GPIO_TypeDef *gpio = (GPIO_TypeDef*)(port_pin & ~0xf);

    // Enable the GPIO peripheral clock
    uint32_t gpio_idx = ((uintptr_t)gpio - GPIOA_BASE) / (GPIOB_BASE - GPIOA_BASE);
    RCC->AHBxENR |= 1 << (AHBxENR_GPIOAEN_Pos + gpio_idx);
    volatile uint32_t tmp = RCC->AHBxENR; // Delay after enabling clock
    (void)tmp;

    // Configure the pin
    uint32_t pin = port_pin & 0xf;
    gpio->MODER = (gpio->MODER & ~(3 << (2 * pin))) | ((mode & 3) << (2 * pin));
    gpio->OTYPER = (gpio->OTYPER & ~(1 << pin)) | ((mode >> 2) << pin);
    gpio->OSPEEDR = (gpio->OSPEEDR & ~(3 << (2 * pin))) | (2 << (2 * pin)); // full speed
    gpio->PUPDR = (gpio->PUPDR & ~(3 << (2 * pin))) | (pull << (2 * pin));
    gpio->AFR[pin >> 3] = (gpio->AFR[pin >> 3] & ~(15 << (4 * (pin & 7)))) | (alt << (4 * (pin & 7)));
}