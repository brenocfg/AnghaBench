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
 unsigned long HWREG (scalar_t__) ; 
 scalar_t__ MCSPI_O_XFERLEVEL ; 

void
SPIFIFOLevelGet(unsigned long ulBase, unsigned long *pulTxLevel,
                 unsigned long *pulRxLevel)
{
  unsigned long ulRegVal;

  //
  // Read the current configuration
  //
  ulRegVal = HWREG(ulBase + MCSPI_O_XFERLEVEL);

  *pulTxLevel = (ulRegVal & 0xFF);

  *pulRxLevel = ((ulRegVal >> 8) & 0xFF);

}