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
typedef  size_t uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int int64_t ;
struct TYPE_2__ {scalar_t__ range_sw_err; } ;

/* Variables and functions */
 TYPE_1__ bme680_data ; 
 scalar_t__* lookupTable1 ; 
 scalar_t__* lookupTable2 ; 

__attribute__((used)) static uint32_t calc_gas_resistance(uint16_t gas_res_adc, uint8_t gas_range)
{
	int64_t var1;
	uint64_t var2;
	int64_t var3;
	uint32_t calc_gas_res;

	var1 = (int64_t) ((1340 + (5 * (int64_t) bme680_data.range_sw_err)) * ((int64_t) lookupTable1[gas_range])) / 65536;
	var2 = (((int64_t) ((int64_t) gas_res_adc * 32768) - (int64_t) (16777216)) + var1);
	var3 = (((int64_t) lookupTable2[gas_range] * (int64_t) var1) / 512);
	calc_gas_res = (uint32_t) ((var3 + ((int64_t) var2 / 2)) / (int64_t) var2);

	return calc_gas_res;
}