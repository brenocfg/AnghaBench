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
 scalar_t__ HWREG (int /*<<< orphan*/ ) ; 
 unsigned long NUM_INTERRUPTS ; 
 int /*<<< orphan*/  NVIC_VTABLE ; 

void
IntRegister(unsigned long ulInterrupt, void (*pfnHandler)(void))
{
    unsigned long *ulNvicTbl;

    //
    // Check the arguments.
    //
    ASSERT(ulInterrupt < NUM_INTERRUPTS);

    ulNvicTbl = (unsigned long *)HWREG(NVIC_VTABLE);
    ulNvicTbl[ulInterrupt]= (unsigned long)pfnHandler;
}