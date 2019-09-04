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
 int /*<<< orphan*/  UtilsDelay (int) ; 

unsigned long PRCMHIBRegRead(unsigned long ulRegAddr)
{
  unsigned long ulValue;

  //
  // Read the Reg value
  //
  ulValue = HWREG(ulRegAddr);

  //
  // Wait for 200 uSec
  //
  UtilsDelay((80*200)/3);

  //
  // Return the value
  //
  return ulValue;
}