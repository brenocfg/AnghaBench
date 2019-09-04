#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* mp_hal_pin_obj_t ;
struct TYPE_5__ {int OSPEEDR; } ;
struct TYPE_4__ {int pin; TYPE_2__* gpio; } ;
typedef  TYPE_2__ GPIO_TypeDef ;

/* Variables and functions */

void mp_hal_pin_config_speed(mp_hal_pin_obj_t pin_obj, uint32_t speed) {
    GPIO_TypeDef *gpio = pin_obj->gpio;
    uint32_t pin = pin_obj->pin;
    gpio->OSPEEDR = (gpio->OSPEEDR & ~(3 << (2 * pin))) | (speed << (2 * pin));
}