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
struct max8925_power_info {int /*<<< orphan*/  adc; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX8925_ADC_ISNS ; 
 int MAX8925_ADC_VBBATT ; 
 int MAX8925_ADC_VCHG ; 
 int MAX8925_ADC_VMBATT ; 
 int MAX8925_CMD_ISNS ; 
 int MAX8925_CMD_VBBATT ; 
 int MAX8925_CMD_VCHG ; 
 int MAX8925_CMD_VMBATT ; 
#define  MEASURE_ISNS 131 
#define  MEASURE_VBBATT 130 
#define  MEASURE_VCHG 129 
#define  MEASURE_VMBATT 128 
 int /*<<< orphan*/  max8925_bulk_read (int /*<<< orphan*/ ,int,int,unsigned char*) ; 
 int /*<<< orphan*/  max8925_reg_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_measure(struct max8925_power_info *info, int type)
{
	unsigned char buf[2] = {0, 0};
	int meas_cmd;
	int meas_reg = 0, ret;

	switch (type) {
	case MEASURE_VCHG:
		meas_cmd = MAX8925_CMD_VCHG;
		meas_reg = MAX8925_ADC_VCHG;
		break;
	case MEASURE_VBBATT:
		meas_cmd = MAX8925_CMD_VBBATT;
		meas_reg = MAX8925_ADC_VBBATT;
		break;
	case MEASURE_VMBATT:
		meas_cmd = MAX8925_CMD_VMBATT;
		meas_reg = MAX8925_ADC_VMBATT;
		break;
	case MEASURE_ISNS:
		meas_cmd = MAX8925_CMD_ISNS;
		meas_reg = MAX8925_ADC_ISNS;
		break;
	default:
		return -EINVAL;
	}

	max8925_reg_write(info->adc, meas_cmd, 0);
	max8925_bulk_read(info->adc, meas_reg, 2, buf);
	ret = ((buf[0]<<8) | buf[1]) >> 4;

	return ret;
}