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
typedef  int uint32_t ;
typedef  int mp_uint_t ;

/* Variables and functions */
 int HAL_NVIC_INT_CTRL_REG ; 
 int HAL_VECTACTIVE_MASK ; 
 int HAL_tickCount ; 
 scalar_t__ IRQ_STATE_ENABLED ; 
 int /*<<< orphan*/  MP_THREAD_GIL_ENTER () ; 
 int /*<<< orphan*/  MP_THREAD_GIL_EXIT () ; 
 int /*<<< orphan*/  UTILS_DELAY_US_TO_COUNT (int) ; 
 int /*<<< orphan*/  UtilsDelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __WFI () ; 
 int portTICK_PERIOD_MS ; 
 scalar_t__ query_irq () ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void mp_hal_delay_ms(mp_uint_t delay) {
    // only if we are not within interrupt context and interrupts are enabled
    if ((HAL_NVIC_INT_CTRL_REG & HAL_VECTACTIVE_MASK) == 0 && query_irq() == IRQ_STATE_ENABLED) {
        MP_THREAD_GIL_EXIT();
        #ifdef USE_FREERTOS
            vTaskDelay (delay / portTICK_PERIOD_MS);
        #else
            uint32_t start = HAL_tickCount;
            // wraparound of tick is taken care of by 2's complement arithmetic.
            while (HAL_tickCount - start < delay) {
                // enter sleep mode, waiting for (at least) the SysTick interrupt.
                __WFI();
            }
        #endif
        MP_THREAD_GIL_ENTER();
    } else {
        for (int ms = 0; ms < delay; ms++) {
            UtilsDelay(UTILS_DELAY_US_TO_COUNT(1000));
        }
    }
}