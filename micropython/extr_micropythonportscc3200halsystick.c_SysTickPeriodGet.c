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
 int /*<<< orphan*/  NVIC_ST_RELOAD ; 

unsigned long
SysTickPeriodGet(void)
{
    //
    // Return the period of the SysTick counter.
    //
    return(HWREG(NVIC_ST_RELOAD) + 1);
}