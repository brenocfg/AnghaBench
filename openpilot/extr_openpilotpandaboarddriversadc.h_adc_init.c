#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int CCR; } ;
struct TYPE_3__ {int SMPR1; int /*<<< orphan*/  CR2; } ;

/* Variables and functions */
 TYPE_2__* ADC ; 
 TYPE_1__* ADC1 ; 
 int ADC_CCR_TSVREFE ; 
 int ADC_CCR_VBATE ; 
 int /*<<< orphan*/  ADC_CR2_ADON ; 
 int ADC_SMPR1_SMP12 ; 
 int ADC_SMPR1_SMP13 ; 

void adc_init() {
  // global setup
  ADC->CCR = ADC_CCR_TSVREFE | ADC_CCR_VBATE;
  //ADC1->CR2 = ADC_CR2_ADON | ADC_CR2_EOCS | ADC_CR2_DDS;
  ADC1->CR2 = ADC_CR2_ADON;

  // long
  //ADC1->SMPR1 = ADC_SMPR1_SMP10 | ADC_SMPR1_SMP11 | ADC_SMPR1_SMP12 | ADC_SMPR1_SMP13;
  ADC1->SMPR1 = ADC_SMPR1_SMP12 | ADC_SMPR1_SMP13;
}