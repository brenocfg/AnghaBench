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
 int HWREG (scalar_t__) ; 
 scalar_t__ MCASP_O_RXBUF0 ; 
 scalar_t__ MCASP_O_RXSTAT ; 
 int MCASP_RXSTAT_RDATA ; 

long I2SDataGetNonBlocking(unsigned long ulBase, unsigned long ulDataLine,
                unsigned long *pulData)
{

  //
  // Compute register the offeset
  //
  ulDataLine = (ulDataLine-1) << 2;

  //
  // Check if data is available in FIFO
  //
  if(HWREG(ulBase + MCASP_O_RXSTAT) & MCASP_RXSTAT_RDATA)
  {
    //
    // Read the Data
    //
    *pulData = HWREG(ulBase + MCASP_O_RXBUF0 + ulDataLine);
    return 0;
  }

  //
  // FIFO is empty
  //
  return -1;
}