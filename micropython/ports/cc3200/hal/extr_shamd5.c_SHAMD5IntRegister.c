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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  INT_SHA ; 
 int /*<<< orphan*/  IntEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntRegister (int /*<<< orphan*/ ,void (*) ()) ; 
 scalar_t__ SHAMD5_BASE ; 

void
SHAMD5IntRegister(uint32_t ui32Base, void(*pfnHandler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == SHAMD5_BASE);

    //
    // Register the interrupt handler.
    //
    IntRegister(INT_SHA, pfnHandler);

    //
    // Enable the interrupt
    //
    IntEnable(INT_SHA);
}