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
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  GPIOB ; 
#define  USB_POWER_CDP 130 
#define  USB_POWER_CLIENT 129 
#define  USB_POWER_DCP 128 
 int /*<<< orphan*/  set_gpio_output (int /*<<< orphan*/ ,int,int) ; 
 int usb_power_mode ; 

void set_usb_power_mode(int mode) {
  switch (mode) {
    case USB_POWER_CLIENT:
      // B2,A13: set client mode
      set_gpio_output(GPIOB, 2, 0);
      set_gpio_output(GPIOA, 13, 1);
      break;
    case USB_POWER_CDP:
      // B2,A13: set CDP mode
      set_gpio_output(GPIOB, 2, 1);
      set_gpio_output(GPIOA, 13, 1);
      break;
    case USB_POWER_DCP:
      // B2,A13: set DCP mode on the charger (breaks USB!)
      set_gpio_output(GPIOB, 2, 0);
      set_gpio_output(GPIOA, 13, 0);
      break;
  }
  usb_power_mode = mode;
}