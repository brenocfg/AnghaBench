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
struct TYPE_4__ {int ODR; } ;
typedef  TYPE_1__ GPIO_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_OUTPUT ; 
 int /*<<< orphan*/  set_gpio_mode (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void set_gpio_output(GPIO_TypeDef *GPIO, int pin, int val) {
  if (val) {
    GPIO->ODR |= (1 << pin);
  } else {
    GPIO->ODR &= ~(1 << pin);
  }
  set_gpio_mode(GPIO, pin, MODE_OUTPUT);
}