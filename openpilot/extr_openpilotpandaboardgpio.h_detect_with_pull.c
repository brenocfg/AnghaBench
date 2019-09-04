#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GPIO_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_INPUT ; 
 int volatile PULL_EFFECTIVE_DELAY ; 
 int PULL_NONE ; 
 int get_gpio_input (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_gpio_mode (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_pullup (int /*<<< orphan*/ *,int,int) ; 

int detect_with_pull(GPIO_TypeDef *GPIO, int pin, int mode) {
  set_gpio_mode(GPIO, pin, MODE_INPUT);
  set_gpio_pullup(GPIO, pin, mode);
  for (volatile int i=0; i<PULL_EFFECTIVE_DELAY; i++);
  int ret = get_gpio_input(GPIO, pin);
  set_gpio_pullup(GPIO, pin, PULL_NONE);
  return ret;
}