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
 int SysTickPeriodGet () ; 
 int SysTickValueGet () ; 
 int disable_irq () ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 int mp_hal_ticks_ms () ; 

mp_uint_t mp_hal_ticks_us(void) {
    mp_uint_t irq_state = disable_irq();
    uint32_t counter = SysTickValueGet();
    uint32_t milliseconds = mp_hal_ticks_ms();
    enable_irq(irq_state);

    uint32_t load = SysTickPeriodGet();
    counter = load - counter; // Convert from decrementing to incrementing
    return (milliseconds * 1000) + ((counter * 1000) / load);
}