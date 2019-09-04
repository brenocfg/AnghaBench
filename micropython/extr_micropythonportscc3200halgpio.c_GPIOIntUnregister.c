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
 int /*<<< orphan*/  IntDisable (unsigned long) ; 
 int /*<<< orphan*/  IntUnregister (unsigned long) ; 

void
GPIOIntUnregister(unsigned long ulPort)
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
    // Disable the GPIO interrupt.
    //
    IntDisable(ulPort);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(ulPort);
}