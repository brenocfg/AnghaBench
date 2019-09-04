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
 unsigned long MCSPI_CH0STAT_RXS ; 
 scalar_t__ MCSPI_O_CH0STAT ; 
 scalar_t__ MCSPI_O_RX0 ; 

void
SPIDataGet(unsigned long ulBase, unsigned long *pulData)
{
  //
  // Wait for Rx data
  //
  while(!(HWREG(ulBase + MCSPI_O_CH0STAT) & MCSPI_CH0STAT_RXS))
  {
  }

  //
  // Read the value
  //
  *pulData = HWREG(ulBase + MCSPI_O_RX0);
}