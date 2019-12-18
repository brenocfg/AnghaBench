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
struct TYPE_2__ {int PSC; int ARR; scalar_t__ SR; int /*<<< orphan*/  DIER; int /*<<< orphan*/  CR1; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 TYPE_1__* TIM4 ; 
 int /*<<< orphan*/  TIM4_IRQn ; 
 int /*<<< orphan*/  TIM_CR1_CEN ; 
 int /*<<< orphan*/  TIM_DIER_UIE ; 

void setup_timer4(void) {
  // setup
  TIM4->PSC = 48-1;          // tick on 1 us
  TIM4->CR1 = TIM_CR1_CEN;   // enable
  TIM4->ARR = 30-1;          // 33.3 kbps

  // in case it's disabled
  NVIC_EnableIRQ(TIM4_IRQn);

  // run the interrupt
  TIM4->DIER = TIM_DIER_UIE; // update interrupt
  TIM4->SR = 0;
}