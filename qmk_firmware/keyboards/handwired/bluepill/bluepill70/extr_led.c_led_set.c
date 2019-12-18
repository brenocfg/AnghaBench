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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOC ; 
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  palClearPad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  palSetPad (int /*<<< orphan*/ ,int) ; 

void led_set(uint8_t usb_led){
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    /* generic STM32F103C8T6 board */
    #ifdef BOARD_GENERIC_STM32_F103
      palClearPad(GPIOC, 13);
    #endif
  } else {
    /* generic STM32F103C8T6 board */
    #ifdef BOARD_GENERIC_STM32_F103
      palSetPad(GPIOC, 13);
    #endif
  }
}