#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int JSQR; int SR; int /*<<< orphan*/  JDR1; int /*<<< orphan*/  CR2; } ;

/* Variables and functions */
 TYPE_1__* ADC1 ; 
 int /*<<< orphan*/  ADC_CR2_JSWSTART ; 
 int ADC_SR_JEOC ; 

uint32_t adc_get(int channel) {
  // includes length
  //ADC1->SQR1 = 0;

  // select channel
  ADC1->JSQR = channel << 15;

  //ADC1->CR1 = ADC_CR1_DISCNUM_0;
  //ADC1->CR1 = ADC_CR1_EOCIE;

  ADC1->SR &= ~(ADC_SR_JEOC);
  ADC1->CR2 |= ADC_CR2_JSWSTART;
  while (!(ADC1->SR & ADC_SR_JEOC));

  return ADC1->JDR1;
}