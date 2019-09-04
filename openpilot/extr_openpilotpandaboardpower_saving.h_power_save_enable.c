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
typedef  int /*<<< orphan*/  uart_ring ;
struct TYPE_2__ {int PSC; int ARR; int CR1; int /*<<< orphan*/  EGR; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN1 ; 
 int /*<<< orphan*/  CAN2 ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  POWER_SAVE_STATUS_SWITCHING ; 
 TYPE_1__* TIM6 ; 
 int TIM_CR1_CEN ; 
 int TIM_CR1_OPM ; 
 int TIM_CR1_URS ; 
 int /*<<< orphan*/  TIM_EGR_UG ; 
 int /*<<< orphan*/ * get_ring_by_number (int) ; 
 scalar_t__ is_grey_panda ; 
 int /*<<< orphan*/  power_save_status ; 
 int /*<<< orphan*/  putc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  set_can_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_output (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void power_save_enable(void) {
  power_save_status = POWER_SAVE_STATUS_SWITCHING;
  puts("Saving power\n");
  //Turn off can transciever
  set_can_enable(CAN1, 0);
  set_can_enable(CAN2, 0);
#ifdef PANDA
  set_can_enable(CAN3, 0);
#endif

  //Turn off GMLAN
  set_gpio_output(GPIOB, 14, 0);
  set_gpio_output(GPIOB, 15, 0);

#ifdef PANDA
  //Turn off LIN K
  if (revision == PANDA_REV_C) {
    set_gpio_output(GPIOB, 7, 0); // REV C
  } else {
    set_gpio_output(GPIOB, 4, 0); // REV AB
  }
  // LIN L
  set_gpio_output(GPIOA, 14, 0);
#endif

  if (is_grey_panda) {
    char* UBLOX_SLEEP_MSG = "\xb5\x62\x06\x04\x04\x00\x01\x00\x08\x00\x17\x78";
    int len = 12;
    uart_ring *ur = get_ring_by_number(1);
    for (int i = 0; i < len; i++) while (!putc(ur, UBLOX_SLEEP_MSG[i]));
  }

  //Setup timer for can enable
  TIM6->PSC = 48-1; // tick on 1 us

  TIM6->ARR = 12; // 12us
  // Enable, One-Pulse Mode, Only overflow interrupt
  TIM6->CR1 = TIM_CR1_CEN | TIM_CR1_OPM | TIM_CR1_URS;
  TIM6->EGR = TIM_EGR_UG;
  TIM6->CR1 |= TIM_CR1_CEN;
}