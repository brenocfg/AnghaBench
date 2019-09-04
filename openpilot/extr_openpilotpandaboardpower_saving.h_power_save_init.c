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
struct TYPE_2__ {int PSC; int ARR; int CR1; int /*<<< orphan*/  DIER; int /*<<< orphan*/  EGR; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 TYPE_1__* TIM6 ; 
 int /*<<< orphan*/  TIM6_DAC_IRQn ; 
 int TIM_CR1_CEN ; 
 int TIM_CR1_OPM ; 
 int TIM_CR1_URS ; 
 int /*<<< orphan*/  TIM_DIER_UIE ; 
 int /*<<< orphan*/  TIM_EGR_UG ; 
 int /*<<< orphan*/  puts (char*) ; 

void power_save_init(void) {
  puts("Saving power init\n");
  TIM6->PSC = 48000-1; // tick on 1 ms


  TIM6->ARR = 10000; // 10s
  // Enable, One-Pulse Mode, Only overflow interrupt
  TIM6->CR1 = TIM_CR1_CEN | TIM_CR1_OPM | TIM_CR1_URS;
  TIM6->EGR = TIM_EGR_UG;
  NVIC_EnableIRQ(TIM6_DAC_IRQn);
  puts("Saving power init done\n");
  TIM6->DIER = TIM_DIER_UIE;
  TIM6->CR1 |= TIM_CR1_CEN;
}