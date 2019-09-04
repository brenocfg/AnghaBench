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
struct da9052_battery {int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int DA9052_VC_TBL_SZ ; 
 int EIO ; 
 int da9052_adc_read_temp (int /*<<< orphan*/ ) ; 
 int da9052_bat_interpolate (int,int,int,int,int) ; 
 int da9052_bat_read_volt (struct da9052_battery*,int*) ; 
 int da9052_determine_vc_tbl_index (int) ; 
 int*** vc_tbl ; 

__attribute__((used)) static int da9052_bat_read_capacity(struct da9052_battery *bat, int *capacity)
{
	int adc_temp;
	int bat_voltage;
	int vbat_lower;
	int vbat_upper;
	int level_upper;
	int level_lower;
	int ret;
	int flag;
	int i = 0;
	int j;

	ret = da9052_bat_read_volt(bat, &bat_voltage);
	if (ret < 0)
		return ret;

	adc_temp = da9052_adc_read_temp(bat->da9052);
	if (adc_temp < 0)
		return adc_temp;

	i = da9052_determine_vc_tbl_index(adc_temp);

	if (bat_voltage >= vc_tbl[i][0][0]) {
		*capacity = 100;
		return 0;
	}
	if (bat_voltage <= vc_tbl[i][DA9052_VC_TBL_SZ - 1][0]) {
		*capacity = 0;
		return 0;
	}
	flag = 0;

	for (j = 0; j < (DA9052_VC_TBL_SZ-1); j++) {
		if ((bat_voltage <= vc_tbl[i][j][0]) &&
		    (bat_voltage >= vc_tbl[i][j + 1][0])) {
			vbat_upper = vc_tbl[i][j][0];
			vbat_lower = vc_tbl[i][j + 1][0];
			level_upper = vc_tbl[i][j][1];
			level_lower = vc_tbl[i][j + 1][1];
			flag = 1;
			break;
		}
	}
	if (!flag)
		return -EIO;

	*capacity = da9052_bat_interpolate(vbat_lower, vbat_upper, level_lower,
					   level_upper, bat_voltage);

	return 0;
}