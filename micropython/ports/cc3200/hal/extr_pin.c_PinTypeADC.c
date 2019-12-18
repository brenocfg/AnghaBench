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
 int /*<<< orphan*/  PIN_TYPE_ANALOG ; 
 int /*<<< orphan*/  PinConfigSet (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void PinTypeADC(unsigned long ulPin,unsigned long ulPinMode)
{
  //
  // Configure the Pin
  //
  PinConfigSet(ulPin,PIN_STRENGTH_2MA,PIN_TYPE_ANALOG);
}