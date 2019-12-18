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
typedef  int tBoolean ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int HWREG (scalar_t__) ; 
 unsigned long WDT_BASE ; 
 int WDT_CTL_INTEN ; 
 scalar_t__ WDT_O_CTL ; 

tBoolean
WatchdogRunning(unsigned long ulBase)
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WDT_BASE));

    //
    // See if the watchdog timer module is enabled, and return.
    //
    return(HWREG(ulBase + WDT_O_CTL) & WDT_CTL_INTEN);
}