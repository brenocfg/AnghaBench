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
 int /*<<< orphan*/  MODE_ALTERNATE ; 
 int /*<<< orphan*/  set_gpio_mode (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void set_gpio_alternate(GPIO_TypeDef *GPIO, int pin, int mode) {
  uint32_t tmp = GPIO->AFR[pin>>3];
  tmp &= ~(0xF << ((pin&7)*4));
  tmp |= mode << ((pin&7)*4);
  GPIO->AFR[pin>>3] = tmp;
  set_gpio_mode(GPIO, pin, MODE_ALTERNATE);
}