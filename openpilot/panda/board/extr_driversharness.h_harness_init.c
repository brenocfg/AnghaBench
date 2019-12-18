#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {TYPE_1__* harness_config; int /*<<< orphan*/  (* set_led ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  pin_SBU1; int /*<<< orphan*/  GPIO_SBU1; int /*<<< orphan*/  pin_SBU2; int /*<<< orphan*/  GPIO_SBU2; } ;

/* Variables and functions */
 scalar_t__ HARNESS_STATUS_NC ; 
 scalar_t__ HARNESS_STATUS_NORMAL ; 
 int /*<<< orphan*/  LED_BLUE ; 
 int /*<<< orphan*/  MODE_INPUT ; 
 scalar_t__ car_harness_status ; 
 TYPE_2__* current_board ; 
 int /*<<< orphan*/  delay (int) ; 
 scalar_t__ harness_detect_orientation () ; 
 int /*<<< orphan*/  harness_setup_ignition_interrupts () ; 
 int /*<<< orphan*/  puth2 (scalar_t__) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  set_gpio_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_intercept_relay (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

void harness_init(void) {
  // delay such that the connection is fully made before trying orientation detection
  current_board->set_led(LED_BLUE, true);
  delay(10000000);
  current_board->set_led(LED_BLUE, false);

  // try to detect orientation
  uint8_t ret = harness_detect_orientation();
  if (ret != HARNESS_STATUS_NC) {
    puts("detected car harness with orientation "); puth2(ret); puts("\n");
    car_harness_status = ret;

    // set the SBU lines to be inputs before using the relay. The lines are not 5V tolerant in ADC mode!
    set_gpio_mode(current_board->harness_config->GPIO_SBU1, current_board->harness_config->pin_SBU1, MODE_INPUT);
    set_gpio_mode(current_board->harness_config->GPIO_SBU2, current_board->harness_config->pin_SBU2, MODE_INPUT);

    // now we have orientation, set pin ignition detection
    if(car_harness_status == HARNESS_STATUS_NORMAL){
      set_gpio_mode(current_board->harness_config->GPIO_SBU2, current_board->harness_config->pin_SBU2, MODE_INPUT);
    } else {
      set_gpio_mode(current_board->harness_config->GPIO_SBU1, current_board->harness_config->pin_SBU1, MODE_INPUT);
    }      

    // keep busses connected by default
    set_intercept_relay(false);

    // setup ignition interrupts
    harness_setup_ignition_interrupts();
  } else {
    puts("failed to detect car harness!\n");
  }
}