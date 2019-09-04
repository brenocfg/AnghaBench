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
 unsigned long ADC_CH_0 ; 
 unsigned long ADC_CH_1 ; 
 unsigned long ADC_CH_2 ; 
 unsigned long ADC_O_adc_ch0_irq_status ; 
 unsigned long APPS_CONFIG_BASE ; 
 unsigned long APPS_CONFIG_O_DMA_DONE_INT_STS_MASKED ; 
 int HWREG (unsigned long) ; 

unsigned long ADCIntStatus(unsigned long ulBase, unsigned long ulChannel)
{
  unsigned long ulOffset;
  unsigned long ulDmaMsk;
  unsigned long ulIntStatus;

  //
  // Get DMA Done interrupt status
  //
  ulDmaMsk = (ulChannel == ADC_CH_0)?0x00001000:
            (ulChannel == ADC_CH_1)?0x00002000:
            (ulChannel == ADC_CH_2)?0x00004000:0x00008000;

  ulIntStatus = HWREG(APPS_CONFIG_BASE +
                     APPS_CONFIG_O_DMA_DONE_INT_STS_MASKED)& ulDmaMsk;


  //
  // Get the interrupt enable register offset for specified channel
  //
  ulOffset = ADC_O_adc_ch0_irq_status + ulChannel;

  //
  // Read ADC interrupt status
  //
  ulIntStatus |= HWREG(ulBase + ulOffset) & 0xf;

  //
  // Return the current interrupt status
  //
  return(ulIntStatus);
}