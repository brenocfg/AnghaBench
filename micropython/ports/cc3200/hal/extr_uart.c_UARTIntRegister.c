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
 int /*<<< orphan*/  IntEnable (unsigned long) ; 
 int /*<<< orphan*/  IntRegister (unsigned long,void (*) ()) ; 
 int /*<<< orphan*/  UARTBaseValid (unsigned long) ; 
 unsigned long UARTIntNumberGet (unsigned long) ; 

void
UARTIntRegister(unsigned long ulBase, void (*pfnHandler)(void))
{
    unsigned long ulInt;

    //
    // Check the arguments.
    //
    ASSERT(UARTBaseValid(ulBase));

    //
    // Determine the interrupt number based on the UART port.
    //

    ulInt = UARTIntNumberGet(ulBase);

    //
    // Register the interrupt handler.
    //
    IntRegister(ulInt, pfnHandler);

    //
    // Enable the UART interrupt.
    //
    IntEnable(ulInt);
}