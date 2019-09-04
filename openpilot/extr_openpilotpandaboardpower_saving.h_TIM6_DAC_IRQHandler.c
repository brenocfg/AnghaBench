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
struct TYPE_2__ {int SR; int /*<<< orphan*/  CR1; } ;

/* Variables and functions */
 TYPE_1__* TIM6 ; 
 int /*<<< orphan*/  TIM_CR1_CEN ; 
 int TIM_SR_UIF ; 

void TIM6_DAC_IRQHandler(void) {
  //Timeout switch to power saving mode.
  if (TIM6->SR & TIM_SR_UIF) {
    TIM6->SR = 0;
#ifdef EON
    if (power_save_status == POWER_SAVE_STATUS_DISABLED) {
      power_save_enable();
    } else if (power_save_status == POWER_SAVE_STATUS_SWITCHING) {
      power_save_enable_can_wake();
    }
#endif
  } else {
    TIM6->CR1 |= TIM_CR1_CEN;
  }
}