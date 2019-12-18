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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADCCHAN_VOLTAGE ; 
 unsigned int adc_get (int /*<<< orphan*/ ) ; 

uint32_t adc_get_voltage(void) {
  // REVC has a 10, 1 (1/11) voltage divider
  // Here is the calculation for the scale (s)
  // ADCV = VIN_S * (1/11) * (4095/3.3)
  // RETVAL = ADCV * s = VIN_S*1000
  // s = 1000/((4095/3.3)*(1/11)) = 8.8623046875

  // Avoid needing floating point math, so output in mV
  return (adc_get(ADCCHAN_VOLTAGE) * 8862U) / 1000U;
}