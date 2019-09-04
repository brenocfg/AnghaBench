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
struct TYPE_2__ {scalar_t__ dig_T3; scalar_t__ dig_T1; scalar_t__ dig_T2; } ;
typedef  int BME280_S32_t ;

/* Variables and functions */
 TYPE_1__ bme280_data ; 
 int bme280_t_fine ; 

__attribute__((used)) static BME280_S32_t bme280_compensate_T(BME280_S32_t adc_T) {
	BME280_S32_t var1, var2, T;
	var1  = ((((adc_T>>3) - ((BME280_S32_t)bme280_data.dig_T1<<1))) * ((BME280_S32_t)bme280_data.dig_T2)) >> 11;
	var2  = (((((adc_T>>4) - ((BME280_S32_t)bme280_data.dig_T1)) * ((adc_T>>4) - ((BME280_S32_t)bme280_data.dig_T1))) >> 12) *
		((BME280_S32_t)bme280_data.dig_T3)) >> 14;
	bme280_t_fine = var1 + var2;
	T  = (bme280_t_fine * 5 + 128) >> 8;
	return T;
}