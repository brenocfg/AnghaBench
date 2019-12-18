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
 unsigned long HWREG (unsigned long) ; 
 unsigned long PAD_CONFIG_BASE ; 
 unsigned long PAD_STRENGTH_MASK ; 
 unsigned long PAD_TYPE_MASK ; 
 unsigned long* g_ulPinToPadMap ; 

void PinConfigGet(unsigned long ulPin,unsigned long  *pulPinStrength,
	       					unsigned long *pulPinType)
{

  unsigned long ulPad;


  //
  // Get the corresponding Pad
  //
  ulPad = g_ulPinToPadMap[ulPin & 0x3F];


  //
  // Calculate the register address
  //
  ulPad = ((ulPad << 2) + PAD_CONFIG_BASE);


  //
  // Get the type
  //
  *pulPinType = (HWREG(ulPad) & PAD_TYPE_MASK);

  //
  // Get the output drive strength
  //
  *pulPinStrength = (HWREG(ulPad) & PAD_STRENGTH_MASK);

}