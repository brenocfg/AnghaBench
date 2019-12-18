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

/* Variables and functions */
 unsigned short RT1011_ADC_SET ; 
 unsigned short RT1011_ADC_SET_1 ; 
 unsigned short RT1011_ADC_SET_4 ; 
 unsigned short RT1011_ADC_SET_5 ; 
 unsigned short RT1011_ANALOG_CTRL ; 
 unsigned short RT1011_A_TIMING_1 ; 
 unsigned short RT1011_BAT_GAIN_1 ; 
 unsigned short RT1011_BQ_10_A2_15_0 ; 
 unsigned short RT1011_BQ_10_PARAMS_CHECK_5 ; 
 unsigned short RT1011_BQ_6_PARAMS_CHECK_5 ; 
 unsigned short RT1011_BQ_7_PARAMS_CHECK_1 ; 
 unsigned short RT1011_CLASS_D_POS ; 
 unsigned short RT1011_CROSS_BQ_SET_1 ; 
 unsigned short RT1011_DAC_SET_1 ; 
 unsigned short RT1011_MIXER_1 ; 
 unsigned short RT1011_POWER_7 ; 
 unsigned short RT1011_POWER_8 ; 
 unsigned short RT1011_RT_DRC_CROSS ; 
 unsigned short RT1011_RT_DRC_POS_8 ; 
 unsigned short RT1011_SINE_GEN_REG_1 ; 
 unsigned short RT1011_SMART_BOOST_TIMING_1 ; 
 unsigned short RT1011_SMART_BOOST_TIMING_36 ; 
 unsigned short RT1011_SPK_PRO_DC_DET_5 ; 
 unsigned short RT1011_SPK_TEMP_PROTECT_0 ; 
 unsigned short RT1011_SPK_TEMP_PROTECT_6 ; 
 unsigned short RT1011_STP_ALPHA_RECIPROCAL_MSB ; 

__attribute__((used)) static bool rt1011_validate_bq_drc_coeff(unsigned short reg)
{
	if ((reg == RT1011_DAC_SET_1) |
		(reg >= RT1011_ADC_SET && reg <= RT1011_ADC_SET_1) |
		(reg == RT1011_ADC_SET_4) |	(reg == RT1011_ADC_SET_5) |
		(reg == RT1011_MIXER_1) |
		(reg == RT1011_A_TIMING_1) |	(reg >= RT1011_POWER_7 &&
		reg <= RT1011_POWER_8) |
		(reg == RT1011_CLASS_D_POS) | (reg == RT1011_ANALOG_CTRL) |
		(reg >= RT1011_SPK_TEMP_PROTECT_0 &&
		reg <= RT1011_SPK_TEMP_PROTECT_6) |
		(reg >= RT1011_SPK_PRO_DC_DET_5 && reg <= RT1011_BAT_GAIN_1) |
		(reg >= RT1011_RT_DRC_CROSS && reg <= RT1011_RT_DRC_POS_8) |
		(reg >= RT1011_CROSS_BQ_SET_1 && reg <= RT1011_BQ_10_A2_15_0) |
		(reg >= RT1011_SMART_BOOST_TIMING_1 &&
		reg <= RT1011_SMART_BOOST_TIMING_36) |
		(reg == RT1011_SINE_GEN_REG_1) |
		(reg >= RT1011_STP_ALPHA_RECIPROCAL_MSB &&
		reg <= RT1011_BQ_6_PARAMS_CHECK_5) |
		(reg >= RT1011_BQ_7_PARAMS_CHECK_1 &&
		reg <= RT1011_BQ_10_PARAMS_CHECK_5))
		return true;

	return false;
}