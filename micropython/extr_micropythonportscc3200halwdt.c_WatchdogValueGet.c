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
 unsigned long HWREG (scalar_t__) ; 
 unsigned long WDT_BASE ; 
 scalar_t__ WDT_O_VALUE ; 

unsigned long
WatchdogValueGet(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WDT_BASE));

    //
    // Get the current watchdog timer register value.
    //
    return(HWREG(ulBase + WDT_O_VALUE));
}