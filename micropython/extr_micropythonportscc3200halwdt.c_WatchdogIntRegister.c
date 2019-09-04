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
 int /*<<< orphan*/  INT_WDT ; 
 int /*<<< orphan*/  IntEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntRegister (int /*<<< orphan*/ ,void (*) ()) ; 
 unsigned long WDT_BASE ; 

void
WatchdogIntRegister(unsigned long ulBase, void (*pfnHandler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT((ulBase == WDT_BASE));

    //
    // Register the interrupt handler and
    // Enable the watchdog timer interrupt.
    //
    IntRegister(INT_WDT, pfnHandler);
    IntEnable(INT_WDT);
}