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

void enable_interrupt_controller()
{
    /** The local interrupt controller can't be enable or disable.
     *  Instead, we are supposed to rely on the interrupt sources
     *  registers to enable or disable their interrupts
     *  
     *  Neverless, we can still change wich core will receive the
     *  interrupts. They go to Core 0 IRQ by default, which is what
     *  we want. This function becomes effectively useless. 
     */
}