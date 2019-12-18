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
 int /*<<< orphan*/  IntEnable (unsigned long) ; 
 int /*<<< orphan*/  IntRegister (unsigned long,void (*) ()) ; 
 unsigned long SPIIntNumberGet (unsigned long) ; 

void
SPIIntRegister(unsigned long ulBase, void(*pfnHandler)(void))
{
    unsigned long ulInt;

    //
    // Determine the interrupt number based on the SPI module
    //
    ulInt = SPIIntNumberGet(ulBase);

    //
    // Register the interrupt handler.
    //
    IntRegister(ulInt, pfnHandler);

    //
    // Enable the SPI interrupt.
    //
    IntEnable(ulInt);
}