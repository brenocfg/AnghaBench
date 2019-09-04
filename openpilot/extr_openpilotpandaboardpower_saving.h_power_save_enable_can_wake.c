#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  MCR; } ;
struct TYPE_5__ {int /*<<< orphan*/  MCR; } ;
struct TYPE_4__ {int PSC; int ARR; int CR1; int /*<<< orphan*/  EGR; } ;

/* Variables and functions */
 TYPE_3__* CAN1 ; 
 TYPE_2__* CAN2 ; 
 int /*<<< orphan*/  CAN_MCR_AWUM ; 
 int /*<<< orphan*/  CAN_MCR_SLEEP ; 
 int /*<<< orphan*/  POWER_SAVE_STATUS_ENABLED ; 
 TYPE_1__* TIM6 ; 
 int TIM_CR1_OPM ; 
 int TIM_CR1_URS ; 
 int /*<<< orphan*/  TIM_EGR_UG ; 
 int /*<<< orphan*/  power_save_status ; 
 int /*<<< orphan*/  puts (char*) ; 

void power_save_enable_can_wake(void) {
  // CAN Automatic Wake must be done a little while after the sleep
  // On some cars turning off the can transciver can trigger the wakeup
  power_save_status = POWER_SAVE_STATUS_ENABLED;
  puts("Turning can off\n");
  CAN1->MCR |= CAN_MCR_SLEEP;
  CAN1->MCR |= CAN_MCR_AWUM;

  CAN2->MCR |= CAN_MCR_SLEEP;
  CAN2->MCR |= CAN_MCR_AWUM;
#ifdef PANDA
  CAN3->MCR |= CAN_MCR_SLEEP;
  CAN3->MCR |= CAN_MCR_AWUM;
#endif

  //set timer back
  TIM6->PSC = 48000-1; // tick on 1 ms
  TIM6->ARR = 10000; // 10s
  // Enable, One-Pulse Mode, Only overflow interrupt
  TIM6->CR1 = TIM_CR1_OPM | TIM_CR1_URS;
  TIM6->EGR = TIM_EGR_UG;
}