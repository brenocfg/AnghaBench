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
 int /*<<< orphan*/  GPIOC ; 
 int /*<<< orphan*/  LED_GREEN ; 
 int /*<<< orphan*/  LED_RED ; 
 int /*<<< orphan*/  MODE_ANALOG ; 
 int /*<<< orphan*/  common_init_gpio () ; 
 int /*<<< orphan*/  pedal_enable_can_transcievers (int) ; 
 int /*<<< orphan*/  pedal_set_led (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_gpio_mode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void pedal_init(void) {
  common_init_gpio();

  // C0, C1: Throttle inputs
  set_gpio_mode(GPIOC, 0, MODE_ANALOG);
  set_gpio_mode(GPIOC, 1, MODE_ANALOG);
  // DAC outputs on A4 and A5
  //   apparently they don't need GPIO setup

  // Enable transciever
  pedal_enable_can_transcievers(true);

  // Disable LEDs
  pedal_set_led(LED_RED, false);
  pedal_set_led(LED_GREEN, false);
}