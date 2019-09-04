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
struct TYPE_2__ {int KR; int RLR; scalar_t__ PR; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CAN_LIVE ; 
 TYPE_1__* IWDG ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIM3 ; 
 int /*<<< orphan*/  TIM3_IRQn ; 
 int /*<<< orphan*/  __disable_irq () ; 
 int /*<<< orphan*/  __enable_irq () ; 
 int /*<<< orphan*/  adc_init () ; 
 int /*<<< orphan*/  can_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_silent ; 
 int /*<<< orphan*/  clock_init () ; 
 int /*<<< orphan*/  dac_init () ; 
 int /*<<< orphan*/  gpio_init () ; 
 int /*<<< orphan*/  pedal () ; 
 int /*<<< orphan*/  periph_init () ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  timer_init (int /*<<< orphan*/ ,int) ; 

int main() {
  __disable_irq();

  // init devices
  clock_init();
  periph_init();
  gpio_init();

#ifdef PEDAL_USB
  // enable USB
  usb_init();
#endif

  // pedal stuff
  dac_init();
  adc_init();

  // init can
  can_silent = ALL_CAN_LIVE;
  can_init(0);

  // 48mhz / 65536 ~= 732
  timer_init(TIM3, 15);
  NVIC_EnableIRQ(TIM3_IRQn);

  // setup watchdog
  IWDG->KR = 0x5555;
  IWDG->PR = 0;          // divider /4
  // 0 = 0.125 ms, let's have a 50ms watchdog
  IWDG->RLR = 400 - 1;
  IWDG->KR = 0xCCCC;

  puts("**** INTERRUPTS ON ****\n");
  __enable_irq();


  // main pedal loop
  while (1) {
    pedal();
  }

  return 0;
}