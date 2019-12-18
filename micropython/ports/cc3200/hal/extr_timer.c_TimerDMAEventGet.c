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
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 unsigned long HWREG (scalar_t__) ; 
 scalar_t__ TIMER_O_DMAEV ; 
 int /*<<< orphan*/  TimerBaseValid (unsigned long) ; 

unsigned long
TimerDMAEventGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT(TimerBaseValid(ulBase));

    //
    // Return the current DMA triggers.
    //
    return(HWREG(ulBase + TIMER_O_DMAEV));
}