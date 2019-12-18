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
struct TYPE_3__ {unsigned int OTYPER; } ;
typedef  TYPE_1__ GPIO_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_CRITICAL () ; 
 int /*<<< orphan*/  EXIT_CRITICAL () ; 
 unsigned int OUTPUT_TYPE_OPEN_DRAIN ; 

void set_gpio_output_type(GPIO_TypeDef *GPIO, unsigned int pin, unsigned int output_type){
  ENTER_CRITICAL();
  if(output_type == OUTPUT_TYPE_OPEN_DRAIN) {
    GPIO->OTYPER |= (1U << pin);
  } else {
    GPIO->OTYPER &= ~(1U << pin);
  }
  EXIT_CRITICAL();
}