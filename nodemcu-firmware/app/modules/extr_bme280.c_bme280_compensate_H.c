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
struct TYPE_2__ {scalar_t__ dig_H1; scalar_t__ dig_H2; scalar_t__ dig_H3; scalar_t__ dig_H6; scalar_t__ dig_H5; scalar_t__ dig_H4; } ;
typedef  int /*<<< orphan*/  BME280_U32_t ;
typedef  int BME280_S32_t ;

/* Variables and functions */
 TYPE_1__ bme280_data ; 
 int bme280_t_fine ; 

__attribute__((used)) static BME280_U32_t bme280_compensate_H(BME280_S32_t adc_H) {
	BME280_S32_t v_x1_u32r;

	v_x1_u32r = (bme280_t_fine - ((BME280_S32_t)76800));
	v_x1_u32r = (((((adc_H << 14) - (((BME280_S32_t)bme280_data.dig_H4) << 20) - (((BME280_S32_t)bme280_data.dig_H5) * v_x1_u32r)) +
		((BME280_S32_t)16384)) >> 15) * (((((((v_x1_u32r * ((BME280_S32_t)bme280_data.dig_H6)) >> 10) * (((v_x1_u32r *
		((BME280_S32_t)bme280_data.dig_H3)) >> 11) + ((BME280_S32_t)32768))) >> 10) + ((BME280_S32_t)2097152)) *
		((BME280_S32_t)bme280_data.dig_H2) + 8192) >> 14));
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((BME280_S32_t)bme280_data.dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
	v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
	v_x1_u32r = v_x1_u32r>>12;
	return (BME280_U32_t)((v_x1_u32r * 1000)>>10);
}