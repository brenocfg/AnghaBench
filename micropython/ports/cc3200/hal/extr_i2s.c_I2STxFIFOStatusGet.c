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
 scalar_t__ MCASP_0_WFIFOSTS ; 

unsigned long I2STxFIFOStatusGet(unsigned long ulBase)
{
  //
  // Return transmit FIFO level
  //
  return HWREG(ulBase + MCASP_0_WFIFOSTS);
}