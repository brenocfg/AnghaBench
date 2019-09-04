#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int PUPDR; } ;
typedef  TYPE_1__ GPIO_TypeDef ;

/* Variables and functions */

void set_gpio_pullup(GPIO_TypeDef *GPIO, int pin, int mode) {
  uint32_t tmp = GPIO->PUPDR;
  tmp &= ~(3 << (pin*2));
  tmp |= (mode << (pin*2));
  GPIO->PUPDR = tmp;
}