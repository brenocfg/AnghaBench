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

/* Variables and functions */
#define  ESP_BOOTMODE 130 
#define  ESP_DISABLED 129 
#define  ESP_ENABLED 128 
 int /*<<< orphan*/  GPIOC ; 
 int /*<<< orphan*/  set_gpio_output (int /*<<< orphan*/ ,int,int) ; 

void set_esp_mode(int mode) {
  switch (mode) {
    case ESP_DISABLED:
      // ESP OFF
      set_gpio_output(GPIOC, 14, 0);
      set_gpio_output(GPIOC, 5, 0);
      break;
    case ESP_ENABLED:
      // ESP ON
      set_gpio_output(GPIOC, 14, 1);
      set_gpio_output(GPIOC, 5, 1);
      break;
    case ESP_BOOTMODE:
      set_gpio_output(GPIOC, 14, 1);
      set_gpio_output(GPIOC, 5, 0);
      break;
  }
}