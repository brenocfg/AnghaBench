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
 scalar_t__ MMCHS_O_STAT ; 

unsigned long
SDHostIntStatus(unsigned long ulBase)
{
  unsigned long ulIntStatus;

  //
  // Get DMA done interrupt status
  //
  ulIntStatus = HWREG(APPS_CONFIG_BASE + APPS_CONFIG_O_DMA_DONE_INT_STS_RAW);
  ulIntStatus = (ulIntStatus << 30);

  //
  // Return the status of individual interrupt sources
  //
  ulIntStatus |= (HWREG(ulBase + MMCHS_O_STAT) & 0x3FFFFFFF);

  return(ulIntStatus);
}