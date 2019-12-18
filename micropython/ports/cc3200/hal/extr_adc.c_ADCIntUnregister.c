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
 unsigned long INT_ADCCH0 ; 
 unsigned long INT_ADCCH1 ; 
 unsigned long INT_ADCCH2 ; 
 unsigned long INT_ADCCH3 ; 
 int /*<<< orphan*/  IntDisable (unsigned long) ; 
 int /*<<< orphan*/  IntUnregister (unsigned long) ; 

void ADCIntUnregister(unsigned long ulBase, unsigned long ulChannel)
{
  unsigned long ulIntNo;

  //
  // Get the interrupt number associted with the specified channel
  //
  ulIntNo = (ulChannel == ADC_CH_0)? INT_ADCCH0 :
            (ulChannel == ADC_CH_1)? INT_ADCCH1 :
            (ulChannel == ADC_CH_2)? INT_ADCCH2 : INT_ADCCH3;

  //
  // Disable ADC interrupt
  //
  IntDisable(ulIntNo);

  //
  // Unregister the interrupt handler
  //
  IntUnregister(ulIntNo);
}