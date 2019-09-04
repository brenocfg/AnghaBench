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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ IRQ_STATE_ENABLED ; 
 int /*<<< orphan*/  __WFI () ; 
 int /*<<< orphan*/  mp_hal_delay_ms (scalar_t__) ; 
 scalar_t__ query_irq () ; 
 scalar_t__ uwTick ; 

void HAL_Delay(uint32_t Delay) {
    if (query_irq() == IRQ_STATE_ENABLED) {
        // IRQs enabled, so can use systick counter to do the delay
        uint32_t start = uwTick;
        // Wraparound of tick is taken care of by 2's complement arithmetic.
        while (uwTick - start < Delay) {
            // Enter sleep mode, waiting for (at least) the SysTick interrupt.
            __WFI();
        }
    } else {
        // IRQs disabled, use mp_hal_delay_ms routine.
        mp_hal_delay_ms(Delay);
    }
}