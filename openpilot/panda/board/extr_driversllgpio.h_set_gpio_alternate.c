#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int* AFR; } ;
typedef  TYPE_1__ GPIO_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_CRITICAL () ; 
 int /*<<< orphan*/  EXIT_CRITICAL () ; 
 int /*<<< orphan*/  MODE_ALTERNATE ; 
 int /*<<< orphan*/  set_gpio_mode (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 

void set_gpio_alternate(GPIO_TypeDef *GPIO, unsigned int pin, unsigned int mode) {
  ENTER_CRITICAL();
  uint32_t tmp = GPIO->AFR[pin >> 3U];
  tmp &= ~(0xFU << ((pin & 7U) * 4U));
  tmp |= mode << ((pin & 7U) * 4U);
  GPIO->AFR[pin >> 3] = tmp;
  set_gpio_mode(GPIO, pin, MODE_ALTERNATE);
  EXIT_CRITICAL();
}