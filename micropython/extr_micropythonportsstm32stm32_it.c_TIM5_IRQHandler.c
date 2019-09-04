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
 int /*<<< orphan*/  HAL_TIM_IRQHandler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQ_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIM5_Handle ; 
 int /*<<< orphan*/  TIM5_IRQn ; 
 int /*<<< orphan*/  timer_irq_handler (int) ; 

void TIM5_IRQHandler(void) {
    IRQ_ENTER(TIM5_IRQn);
    timer_irq_handler(5);
    HAL_TIM_IRQHandler(&TIM5_Handle);
    IRQ_EXIT(TIM5_IRQn);
}