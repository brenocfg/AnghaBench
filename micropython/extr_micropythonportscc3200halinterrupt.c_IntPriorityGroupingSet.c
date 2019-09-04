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
typedef  int HWREG ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned long NUM_PRIORITY ; 
 int NVIC_APINT_VECTKEY ; 
 int* g_pulPriority ; 

void
IntPriorityGroupingSet(unsigned long ulBits)
{
    //
    // Check the arguments.
    //
    ASSERT(ulBits < NUM_PRIORITY);

    //
    // Set the priority grouping.
    //
    HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | g_pulPriority[ulBits];
}