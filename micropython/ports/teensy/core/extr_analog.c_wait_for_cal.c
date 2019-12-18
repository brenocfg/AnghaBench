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
typedef  int uint16_t ;

/* Variables and functions */
 int ADC0_CLM0 ; 
 int ADC0_CLM1 ; 
 int ADC0_CLM2 ; 
 int ADC0_CLM3 ; 
 int ADC0_CLM4 ; 
 int ADC0_CLMS ; 
 int ADC0_CLP0 ; 
 int ADC0_CLP1 ; 
 int ADC0_CLP2 ; 
 int ADC0_CLP3 ; 
 int ADC0_CLP4 ; 
 int ADC0_CLPS ; 
 int ADC0_MG ; 
 int ADC0_PG ; 
 int ADC0_SC3 ; 
 int ADC1_CLM0 ; 
 int ADC1_CLM1 ; 
 int ADC1_CLM2 ; 
 int ADC1_CLM3 ; 
 int ADC1_CLM4 ; 
 int ADC1_CLMS ; 
 int ADC1_CLP0 ; 
 int ADC1_CLP1 ; 
 int ADC1_CLP2 ; 
 int ADC1_CLP3 ; 
 int ADC1_CLP4 ; 
 int ADC1_CLPS ; 
 int ADC1_MG ; 
 int ADC1_PG ; 
 int ADC1_SC3 ; 
 int ADC_SC3_CAL ; 
 int /*<<< orphan*/  __disable_irq () ; 
 int /*<<< orphan*/  __enable_irq () ; 
 scalar_t__ calibrating ; 

__attribute__((used)) static void wait_for_cal(void)
{
	uint16_t sum;

	//serial_print("wait_for_cal\n");
#if defined(__MK20DX128__)
	while (ADC0_SC3 & ADC_SC3_CAL) {
		// wait
	}
#elif defined(__MK20DX256__)
	while ((ADC0_SC3 & ADC_SC3_CAL) || (ADC1_SC3 & ADC_SC3_CAL)) {
		// wait
	}
#endif
	__disable_irq();
	if (calibrating) {
		//serial_print("\n");
		sum = ADC0_CLPS + ADC0_CLP4 + ADC0_CLP3 + ADC0_CLP2 + ADC0_CLP1 + ADC0_CLP0;
		sum = (sum / 2) | 0x8000;
		ADC0_PG = sum;
		//serial_print("ADC0_PG = ");
		//serial_phex16(sum);
		//serial_print("\n");
		sum = ADC0_CLMS + ADC0_CLM4 + ADC0_CLM3 + ADC0_CLM2 + ADC0_CLM1 + ADC0_CLM0;
		sum = (sum / 2) | 0x8000;
		ADC0_MG = sum;
		//serial_print("ADC0_MG = ");
		//serial_phex16(sum);
		//serial_print("\n");
#if defined(__MK20DX256__)
		sum = ADC1_CLPS + ADC1_CLP4 + ADC1_CLP3 + ADC1_CLP2 + ADC1_CLP1 + ADC1_CLP0;
		sum = (sum / 2) | 0x8000;
		ADC1_PG = sum;
		sum = ADC1_CLMS + ADC1_CLM4 + ADC1_CLM3 + ADC1_CLM2 + ADC1_CLM1 + ADC1_CLM0;
		sum = (sum / 2) | 0x8000;
		ADC1_MG = sum;
#endif
		calibrating = 0;
	}
	__enable_irq();
}