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
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned long INT_TIMERA0A ; 
 unsigned long INT_TIMERA1A ; 
 unsigned long INT_TIMERA2A ; 
 unsigned long INT_TIMERA3A ; 
 int /*<<< orphan*/  IntDisable (unsigned long) ; 
 int /*<<< orphan*/  IntUnregister (unsigned long) ; 
 unsigned long TIMERA0_BASE ; 
 unsigned long TIMERA1_BASE ; 
 unsigned long TIMERA2_BASE ; 
 unsigned long TIMER_A ; 
 unsigned long TIMER_B ; 
 unsigned long TIMER_BOTH ; 
 int TimerBaseValid (unsigned long) ; 

void
TimerIntUnregister(unsigned long ulBase, unsigned long ulTimer)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    //
    // Get the interrupt number for this timer module.
    //

    ulBase = ((ulBase == TIMERA0_BASE) ? INT_TIMERA0A :
              ((ulBase == TIMERA1_BASE) ? INT_TIMERA1A :
               ((ulBase == TIMERA2_BASE) ? INT_TIMERA2A : INT_TIMERA3A)));



    //
    // Unregister the interrupt handler for timer A if requested.
    //
    if(ulTimer & TIMER_A)
    {
        //
        // Disable the interrupt.
        //
        IntDisable(ulBase);

        //
        // Unregister the interrupt handler.
        //
        IntUnregister(ulBase);
    }

    //
    // Unregister the interrupt handler for timer B if requested.
    //
    if(ulTimer & TIMER_B)
    {
        //
        // Disable the interrupt.
        //
        IntDisable(ulBase + 1);

        //
        // Unregister the interrupt handler.
        //
        IntUnregister(ulBase + 1);
    }
}