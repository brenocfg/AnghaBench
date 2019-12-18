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
 unsigned long HWREG (int /*<<< orphan*/ ) ; 
 unsigned long NUM_PRIORITY ; 
 int /*<<< orphan*/  NVIC_APINT ; 
 unsigned long NVIC_APINT_PRIGROUP_M ; 
 unsigned long* g_pulPriority ; 

unsigned long
IntPriorityGroupingGet(void)
{
    unsigned long ulLoop, ulValue;

    //
    // Read the priority grouping.
    //
    ulValue = HWREG(NVIC_APINT) & NVIC_APINT_PRIGROUP_M;

    //
    // Loop through the priority grouping values.
    //
    for(ulLoop = 0; ulLoop < NUM_PRIORITY; ulLoop++)
    {
        //
        // Stop looping if this value matches.
        //
        if(ulValue == g_pulPriority[ulLoop])
        {
            break;
        }
    }

    //
    // Return the number of priority bits.
    //
    return(ulLoop);
}