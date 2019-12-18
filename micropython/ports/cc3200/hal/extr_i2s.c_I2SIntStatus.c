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
 scalar_t__ APPS_CONFIG_BASE ; 
 scalar_t__ APPS_CONFIG_O_DMA_DONE_INT_STS_RAW ; 
 int HWREG (scalar_t__) ; 
 scalar_t__ MCASP_O_RXSTAT ; 
 scalar_t__ MCASP_O_TXSTAT ; 

unsigned long I2SIntStatus(unsigned long ulBase)
{
  unsigned long ulStatus;

  //
  // Get DMA interrupt status
  //
  ulStatus =
    HWREG(APPS_CONFIG_BASE + APPS_CONFIG_O_DMA_DONE_INT_STS_RAW) << 20;

  ulStatus &= 0xC0000000;

  //
  // Read Tx Interrupt status
  //
  ulStatus |= HWREG(ulBase + MCASP_O_TXSTAT);

  //
  // Read Rx Interrupt status
  //
  ulStatus |= HWREG(ulBase + MCASP_O_RXSTAT) << 16;

  //
  // Return the status
  //
  return ulStatus;
}