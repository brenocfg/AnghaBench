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
 int HAL_RCC_GetSysClockFreq () ; 
 scalar_t__ IRQ_STATE_ENABLED ; 
 int mp_hal_ticks_us () ; 
 scalar_t__ query_irq () ; 

void mp_hal_delay_us(mp_uint_t usec) {
    if (query_irq() == IRQ_STATE_ENABLED) {
        // IRQs enabled, so can use systick counter to do the delay
        uint32_t start = mp_hal_ticks_us();
        while (mp_hal_ticks_us() - start < usec) {
        }
    } else {
        // IRQs disabled, so need to use a busy loop for the delay
        // sys freq is always a multiple of 2MHz, so division here won't lose precision
        const uint32_t ucount = HAL_RCC_GetSysClockFreq() / 2000000 * usec / 2;
        for (uint32_t count = 0; ++count <= ucount;) {
        }
    }
}