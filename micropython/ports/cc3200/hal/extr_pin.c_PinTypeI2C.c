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
 int /*<<< orphan*/  PIN_STRENGTH_2MA ; 
 int /*<<< orphan*/  PIN_TYPE_OD_PU ; 
 int /*<<< orphan*/  PinConfigSet (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PinModeSet (unsigned long,unsigned long) ; 

void PinTypeI2C(unsigned long ulPin,unsigned long ulPinMode)
{
    //
    // Set the pin to specified mode
    //
    PinModeSet(ulPin,ulPinMode);

    //
    // Set the pin for open-drain operation with a weak pull-up.
    //
    PinConfigSet(ulPin,PIN_STRENGTH_2MA,PIN_TYPE_OD_PU);
}