#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int CCMR2; int /*<<< orphan*/  CCER; } ;

/* Variables and functions */
 TYPE_1__* TIM3 ; 
 int /*<<< orphan*/  TIM_CCER_CC3E ; 
 int TIM_CCMR2_OC3M_1 ; 
 int TIM_CCMR2_OC3M_2 ; 
 int /*<<< orphan*/  timer_init (TYPE_1__*,int) ; 

void fan_init() {
  // timer for fan PWM
  TIM3->CCMR2 = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
  TIM3->CCER = TIM_CCER_CC3E;
  timer_init(TIM3, 10);
}