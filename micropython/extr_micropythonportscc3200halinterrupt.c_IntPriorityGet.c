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
 int HWREG (int /*<<< orphan*/ ) ; 
 unsigned long NUM_INTERRUPTS ; 
 int /*<<< orphan*/ * g_pulRegs ; 

long
IntPriorityGet(unsigned long ulInterrupt)
{
    //
    // Check the arguments.
    //
    ASSERT((ulInterrupt >= 4) && (ulInterrupt < NUM_INTERRUPTS));

    //
    // Return the interrupt priority.
    //
    return((HWREG(g_pulRegs[ulInterrupt >> 2]) >> (8 * (ulInterrupt & 3))) &
           0xFF);
}