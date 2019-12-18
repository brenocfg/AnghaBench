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
struct TYPE_4__ {unsigned int ODR; } ;
typedef  TYPE_1__ GPIO_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_CRITICAL () ; 
 int /*<<< orphan*/  EXIT_CRITICAL () ; 
 int /*<<< orphan*/  MODE_OUTPUT ; 
 int /*<<< orphan*/  set_gpio_mode (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 

void set_gpio_output(GPIO_TypeDef *GPIO, unsigned int pin, bool enabled) {
  ENTER_CRITICAL();
  if (enabled) {
    GPIO->ODR |= (1U << pin);
  } else {
    GPIO->ODR &= ~(1U << pin);
  }
  set_gpio_mode(GPIO, pin, MODE_OUTPUT);
  EXIT_CRITICAL();
}