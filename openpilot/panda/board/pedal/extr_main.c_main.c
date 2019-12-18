#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* init ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAN1 ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIM3 ; 
 int /*<<< orphan*/  TIM3_IRQn ; 
 int /*<<< orphan*/  adc_init () ; 
 int /*<<< orphan*/  clock_init () ; 
 TYPE_1__* current_board ; 
 int /*<<< orphan*/  dac_init () ; 
 int /*<<< orphan*/  detect_board_type () ; 
 int /*<<< orphan*/  detect_configuration () ; 
 int /*<<< orphan*/  disable_interrupts () ; 
 int /*<<< orphan*/  enable_interrupts () ; 
 int /*<<< orphan*/  llcan_init (int /*<<< orphan*/ ) ; 
 int llcan_set_speed (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pedal () ; 
 int /*<<< orphan*/  peripherals_init () ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  timer_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_init () ; 
 int /*<<< orphan*/  watchdog_init () ; 

int main(void) {
  disable_interrupts();

  // init devices
  clock_init();
  peripherals_init();
  detect_configuration();
  detect_board_type();

  // init board
  current_board->init();

#ifdef PEDAL_USB
  // enable USB
  usb_init();
#endif

  // pedal stuff
  dac_init();
  adc_init();

  // init can
  bool llcan_speed_set = llcan_set_speed(CAN1, 5000, false, false);
  if (!llcan_speed_set) {
    puts("Failed to set llcan speed");
  }

  llcan_init(CAN1);

  // 48mhz / 65536 ~= 732
  timer_init(TIM3, 15);
  NVIC_EnableIRQ(TIM3_IRQn);

  watchdog_init();

  puts("**** INTERRUPTS ON ****\n");
  enable_interrupts();

  // main pedal loop
  while (1) {
    pedal();
  }

  return 0;
}