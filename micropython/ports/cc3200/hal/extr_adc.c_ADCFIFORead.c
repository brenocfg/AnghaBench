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
 unsigned long ADC_O_channel0FIFODATA ; 
 unsigned long HWREG (unsigned long) ; 

unsigned long ADCFIFORead(unsigned long ulBase, unsigned long ulChannel)
{
  unsigned long ulOffset;

  //
  // Get the fifo register offset for specified channel
  //
  ulOffset = ADC_O_channel0FIFODATA + ulChannel;

  //
  // Return FIFO level
  //
  return(HWREG(ulBase + ulOffset));
}