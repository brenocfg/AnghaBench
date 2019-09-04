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
 scalar_t__ MMCHS_O_DATA ; 
 scalar_t__ MMCHS_O_PSTATE ; 

void
SDHostDataRead(unsigned long ulBase, unsigned long *pulData)
{
  //
  // Wait until data is available
  //
  while( !(HWREG(ulBase + MMCHS_O_PSTATE) & (1<<11)) )
  {

  }

  //
  // Read the data
  //
  *pulData = HWREG(ulBase + MMCHS_O_DATA);
}