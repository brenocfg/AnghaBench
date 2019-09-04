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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
typedef  int int32_t ;
struct TYPE_2__ {int par_gh3; int par_gh1; int par_gh2; int res_heat_range; int res_heat_val; } ;

/* Variables and functions */
 scalar_t__ amb_temp ; 
 TYPE_1__ bme680_data ; 

__attribute__((used)) static uint8_t calc_heater_res(uint16_t temp)
{
	uint8_t heatr_res;
	int32_t var1;
	int32_t var2;
	int32_t var3;
	int32_t var4;
	int32_t var5;
	int32_t heatr_res_x100;

	if (temp < 200) /* Cap temperature */
		temp = 200;
	else if (temp > 400)
		temp = 400;

	var1 = (((int32_t) amb_temp * bme680_data.par_gh3) / 1000) * 256;
	var2 = (bme680_data.par_gh1 + 784) * (((((bme680_data.par_gh2 + 154009) * temp * 5) / 100) + 3276800) / 10);
	var3 = var1 + (var2 / 2);
	var4 = (var3 / (bme680_data.res_heat_range + 4));
	var5 = (131 * bme680_data.res_heat_val) + 65536;
	heatr_res_x100 = (int32_t) (((var4 / var5) - 250) * 34);
	heatr_res = (uint8_t) ((heatr_res_x100 + 50) / 100);

	return heatr_res;
}