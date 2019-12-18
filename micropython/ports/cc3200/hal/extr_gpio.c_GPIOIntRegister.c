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
 int /*<<< orphan*/  GPIOBaseValid (unsigned long) ; 
 unsigned long GPIOGetIntNumber (unsigned long) ; 
 int /*<<< orphan*/  IntEnable (unsigned long) ; 
 int /*<<< orphan*/  IntRegister (unsigned long,void (*) ()) ; 

void
GPIOIntRegister(unsigned long ulPort, void (*pfnIntHandler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT(GPIOBaseValid(ulPort));

    //
    // Get the interrupt number associated with the specified GPIO.
    //
    ulPort = GPIOGetIntNumber(ulPort);

    //
    // Register the interrupt handler.
    //
    IntRegister(ulPort, pfnIntHandler);

    //
    // Enable the GPIO interrupt.
    //
    IntEnable(ulPort);
}