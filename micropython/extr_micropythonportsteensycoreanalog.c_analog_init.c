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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ ADC0_CFG1 ; 
 scalar_t__ ADC0_CFG2 ; 
 int /*<<< orphan*/  ADC0_SC2 ; 
 scalar_t__ ADC0_SC3 ; 
 scalar_t__ ADC_CFG1_10BIT ; 
 scalar_t__ ADC_CFG1_12BIT ; 
 scalar_t__ ADC_CFG1_16BIT ; 
 scalar_t__ ADC_CFG1_8BIT ; 
 scalar_t__ ADC_CFG1_ADLSMP ; 
 scalar_t__ ADC_CFG1_MODE (int) ; 
 scalar_t__ ADC_CFG2_ADLSTS (int) ; 
 scalar_t__ ADC_CFG2_MUXSEL ; 
 int /*<<< orphan*/  ADC_SC2_REFSEL (int) ; 
 scalar_t__ ADC_SC3_AVGE ; 
 scalar_t__ ADC_SC3_AVGS (int) ; 
 scalar_t__ ADC_SC3_CAL ; 
 int VREF_SC ; 
 int VREF_TRM ; 
 int analog_config_bits ; 
 int analog_num_average ; 
 scalar_t__ analog_reference_internal ; 
 int calibrating ; 

void analog_init(void)
{
	uint32_t num;

	VREF_TRM = 0x60;
	VREF_SC = 0xE1;		// enable 1.2 volt ref

	if (analog_config_bits == 8) {
		ADC0_CFG1 = ADC_CFG1_8BIT + ADC_CFG1_MODE(0);
		ADC0_CFG2 = ADC_CFG2_MUXSEL + ADC_CFG2_ADLSTS(3);
		#if defined(__MK20DX256__)
		ADC1_CFG1 = ADC_CFG1_8BIT + ADC_CFG1_MODE(0);
		ADC1_CFG2 = ADC_CFG2_MUXSEL + ADC_CFG2_ADLSTS(3);
		#endif
	} else if (analog_config_bits == 10) {
		ADC0_CFG1 = ADC_CFG1_10BIT + ADC_CFG1_MODE(2) + ADC_CFG1_ADLSMP;
		ADC0_CFG2 = ADC_CFG2_MUXSEL + ADC_CFG2_ADLSTS(3);
		#if defined(__MK20DX256__)
		ADC1_CFG1 = ADC_CFG1_10BIT + ADC_CFG1_MODE(2) + ADC_CFG1_ADLSMP;
		ADC1_CFG2 = ADC_CFG2_MUXSEL + ADC_CFG2_ADLSTS(3);
		#endif
	} else if (analog_config_bits == 12) {
		ADC0_CFG1 = ADC_CFG1_12BIT + ADC_CFG1_MODE(1) + ADC_CFG1_ADLSMP;
		ADC0_CFG2 = ADC_CFG2_MUXSEL + ADC_CFG2_ADLSTS(2);
		#if defined(__MK20DX256__)
		ADC1_CFG1 = ADC_CFG1_12BIT + ADC_CFG1_MODE(1) + ADC_CFG1_ADLSMP;
		ADC1_CFG2 = ADC_CFG2_MUXSEL + ADC_CFG2_ADLSTS(2);
		#endif
	} else {
		ADC0_CFG1 = ADC_CFG1_16BIT + ADC_CFG1_MODE(3) + ADC_CFG1_ADLSMP;
		ADC0_CFG2 = ADC_CFG2_MUXSEL + ADC_CFG2_ADLSTS(2);
		#if defined(__MK20DX256__)
		ADC1_CFG1 = ADC_CFG1_16BIT + ADC_CFG1_MODE(3) + ADC_CFG1_ADLSMP;
		ADC1_CFG2 = ADC_CFG2_MUXSEL + ADC_CFG2_ADLSTS(2);
		#endif
	}

	if (analog_reference_internal) {
		ADC0_SC2 = ADC_SC2_REFSEL(1); // 1.2V ref
		#if defined(__MK20DX256__)
		ADC1_SC2 = ADC_SC2_REFSEL(1); // 1.2V ref
		#endif
	} else {
		ADC0_SC2 = ADC_SC2_REFSEL(0); // vcc/ext ref
		#if defined(__MK20DX256__)
		ADC1_SC2 = ADC_SC2_REFSEL(0); // vcc/ext ref
		#endif
	}

	num = analog_num_average;
	if (num <= 1) {
		ADC0_SC3 = ADC_SC3_CAL;  // begin cal
		#if defined(__MK20DX256__)
		ADC1_SC3 = ADC_SC3_CAL;  // begin cal
		#endif
	} else if (num <= 4) {
		ADC0_SC3 = ADC_SC3_CAL + ADC_SC3_AVGE + ADC_SC3_AVGS(0);
		#if defined(__MK20DX256__)
		ADC1_SC3 = ADC_SC3_CAL + ADC_SC3_AVGE + ADC_SC3_AVGS(0);
		#endif
	} else if (num <= 8) {
		ADC0_SC3 = ADC_SC3_CAL + ADC_SC3_AVGE + ADC_SC3_AVGS(1);
		#if defined(__MK20DX256__)
		ADC1_SC3 = ADC_SC3_CAL + ADC_SC3_AVGE + ADC_SC3_AVGS(1);
		#endif
	} else if (num <= 16) {
		ADC0_SC3 = ADC_SC3_CAL + ADC_SC3_AVGE + ADC_SC3_AVGS(2);
		#if defined(__MK20DX256__)
		ADC1_SC3 = ADC_SC3_CAL + ADC_SC3_AVGE + ADC_SC3_AVGS(2);
		#endif
	} else {
		ADC0_SC3 = ADC_SC3_CAL + ADC_SC3_AVGE + ADC_SC3_AVGS(3);
		#if defined(__MK20DX256__)
		ADC1_SC3 = ADC_SC3_CAL + ADC_SC3_AVGE + ADC_SC3_AVGS(3);
		#endif
	}
	calibrating = 1;
}