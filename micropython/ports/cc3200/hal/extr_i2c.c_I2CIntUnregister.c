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
 int /*<<< orphan*/  IntDisable (scalar_t__) ; 
 int /*<<< orphan*/  IntUnregister (scalar_t__) ; 
 int _I2CBaseValid (scalar_t__) ; 
 scalar_t__ _I2CIntNumberGet (scalar_t__) ; 

void
I2CIntUnregister(uint32_t ui32Base)
{
    uint32_t ui32Int;

    //
    // Check the arguments.
    //
    ASSERT(_I2CBaseValid(ui32Base));

    //
    // Determine the interrupt number based on the I2C port.
    //
    ui32Int = _I2CIntNumberGet(ui32Base);

    ASSERT(ui32Int != 0);

    //
    // Disable the interrupt.
    //
    IntDisable(ui32Int);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(ui32Int);
}