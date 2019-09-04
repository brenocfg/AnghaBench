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
 int /*<<< orphan*/  IntEnable (unsigned long) ; 
 int /*<<< orphan*/  IntRegister (unsigned long,void (*) ()) ; 
 unsigned long TIMERA0_BASE ; 
 unsigned long TIMERA1_BASE ; 
 unsigned long TIMERA2_BASE ; 
 unsigned long TIMER_A ; 
 unsigned long TIMER_B ; 
 unsigned long TIMER_BOTH ; 
 int TimerBaseValid (unsigned long) ; 

void
TimerIntRegister(unsigned long ulBase, unsigned long ulTimer,
                 void (*pfnHandler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));
    ASSERT((ulTimer == TIMER_A) || (ulTimer == TIMER_B) ||
           (ulTimer == TIMER_BOTH));

    ulBase = ((ulBase == TIMERA0_BASE) ? INT_TIMERA0A :
              ((ulBase == TIMERA1_BASE) ? INT_TIMERA1A :
               ((ulBase == TIMERA2_BASE) ? INT_TIMERA2A : INT_TIMERA3A)));

    //
    // Register an interrupt handler for timer A if requested.
    //
    if(ulTimer & TIMER_A)
    {
        //
        // Register the interrupt handler.
        //
        IntRegister(ulBase, pfnHandler);

        //
        // Enable the interrupt.
        //
        IntEnable(ulBase);
    }

    //
    // Register an interrupt handler for timer B if requested.
    //
    if(ulTimer & TIMER_B)
    {
        //
        // Register the interrupt handler.
        //
        IntRegister(ulBase + 1, pfnHandler);

        //
        // Enable the interrupt.
        //
        IntEnable(ulBase + 1);
    }
}