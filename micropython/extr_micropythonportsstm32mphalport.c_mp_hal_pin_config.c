#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* mp_hal_pin_obj_t ;
struct TYPE_6__ {int MODER; int OTYPER; int OSPEEDR; int PUPDR; int* AFR; } ;
struct TYPE_5__ {int pin; TYPE_2__* gpio; } ;
typedef  TYPE_2__ GPIO_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  mp_hal_gpio_clock_enable (TYPE_2__*) ; 

void mp_hal_pin_config(mp_hal_pin_obj_t pin_obj, uint32_t mode, uint32_t pull, uint32_t alt) {
    GPIO_TypeDef *gpio = pin_obj->gpio;
    uint32_t pin = pin_obj->pin;
    mp_hal_gpio_clock_enable(gpio);
    gpio->MODER = (gpio->MODER & ~(3 << (2 * pin))) | ((mode & 3) << (2 * pin));
    #if defined(GPIO_ASCR_ASC0)
    // The L4 has a special analog switch to connect the GPIO to the ADC
    gpio->OTYPER = (gpio->OTYPER & ~(1 << pin)) | (((mode >> 2) & 1) << pin);
    gpio->ASCR = (gpio->ASCR & ~(1 << pin)) | ((mode >> 3) & 1) << pin;
    #else
    gpio->OTYPER = (gpio->OTYPER & ~(1 << pin)) | ((mode >> 2) << pin);
    #endif
    gpio->OSPEEDR = (gpio->OSPEEDR & ~(3 << (2 * pin))) | (2 << (2 * pin)); // full speed
    gpio->PUPDR = (gpio->PUPDR & ~(3 << (2 * pin))) | (pull << (2 * pin));
    gpio->AFR[pin >> 3] = (gpio->AFR[pin >> 3] & ~(15 << (4 * (pin & 7)))) | (alt << (4 * (pin & 7)));
}