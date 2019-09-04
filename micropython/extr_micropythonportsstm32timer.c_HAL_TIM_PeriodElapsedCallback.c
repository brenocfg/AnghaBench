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
typedef  int /*<<< orphan*/  TIM_HandleTypeDef ;

/* Variables and functions */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    #if MICROPY_HW_ENABLE_SERVO
    if (htim == &TIM5_Handle) {
        servo_timer_irq_callback();
    }
    #endif
}