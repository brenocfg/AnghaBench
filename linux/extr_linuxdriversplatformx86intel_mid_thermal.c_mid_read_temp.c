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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct thermal_zone_device {struct thermal_device_info* devdata; } ;
struct thermal_device_info {int chnl_addr; int curr_temp; int /*<<< orphan*/  direct; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_MSIC_ADC1CNTL3 ; 
 int /*<<< orphan*/  MSIC_ADCRRDATA_ENBL ; 
 int /*<<< orphan*/  MSIC_ADCTHERM_ENBL ; 
 int adc_to_temp (int /*<<< orphan*/ ,int,int*) ; 
 int intel_msic_reg_read (int,int*) ; 
 int intel_msic_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mid_read_temp(struct thermal_zone_device *tzd, int *temp)
{
	struct thermal_device_info *td_info = tzd->devdata;
	uint16_t adc_val, addr;
	uint8_t data = 0;
	int ret;
	int curr_temp;

	addr = td_info->chnl_addr;

	/* Enable the msic for conversion before reading */
	ret = intel_msic_reg_write(INTEL_MSIC_ADC1CNTL3, MSIC_ADCRRDATA_ENBL);
	if (ret)
		return ret;

	/* Re-toggle the RRDATARD bit (temporary workaround) */
	ret = intel_msic_reg_write(INTEL_MSIC_ADC1CNTL3, MSIC_ADCTHERM_ENBL);
	if (ret)
		return ret;

	/* Read the higher bits of data */
	ret = intel_msic_reg_read(addr, &data);
	if (ret)
		return ret;

	/* Shift bits to accommodate the lower two data bits */
	adc_val = (data << 2);
	addr++;

	ret = intel_msic_reg_read(addr, &data);/* Read lower bits */
	if (ret)
		return ret;

	/* Adding lower two bits to the higher bits */
	data &= 03;
	adc_val += data;

	/* Convert ADC value to temperature */
	ret = adc_to_temp(td_info->direct, adc_val, &curr_temp);
	if (ret == 0)
		*temp = td_info->curr_temp = curr_temp;
	return ret;
}