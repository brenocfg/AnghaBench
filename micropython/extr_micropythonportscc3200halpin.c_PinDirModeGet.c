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
 int HWREG (unsigned long) ; 
 unsigned long PAD_CONFIG_BASE ; 
 unsigned long* g_ulPinToPadMap ; 

unsigned long PinDirModeGet(unsigned long ulPin)
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
  // Return the direction
  //
  return ((HWREG(ulPad) & 0xC00));
}