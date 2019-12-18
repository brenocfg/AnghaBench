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
struct device {int dummy; } ;

/* Variables and functions */
#define  DA9055_ADC_L_GAIN_STATUS 143 
#define  DA9055_ADC_R_GAIN_STATUS 142 
#define  DA9055_ALC_CIC_OP_LVL_DATA 141 
#define  DA9055_AUX_L_GAIN_STATUS 140 
#define  DA9055_AUX_R_GAIN_STATUS 139 
#define  DA9055_DAC_L_GAIN_STATUS 138 
#define  DA9055_DAC_R_GAIN_STATUS 137 
#define  DA9055_HP_L_GAIN_STATUS 136 
#define  DA9055_HP_R_GAIN_STATUS 135 
#define  DA9055_LINE_GAIN_STATUS 134 
#define  DA9055_MIC_L_GAIN_STATUS 133 
#define  DA9055_MIC_R_GAIN_STATUS 132 
#define  DA9055_MIXIN_L_GAIN_STATUS 131 
#define  DA9055_MIXIN_R_GAIN_STATUS 130 
#define  DA9055_PLL_STATUS 129 
#define  DA9055_STATUS1 128 

__attribute__((used)) static bool da9055_volatile_register(struct device *dev,
				     unsigned int reg)
{
	switch (reg) {
	case DA9055_STATUS1:
	case DA9055_PLL_STATUS:
	case DA9055_AUX_L_GAIN_STATUS:
	case DA9055_AUX_R_GAIN_STATUS:
	case DA9055_MIC_L_GAIN_STATUS:
	case DA9055_MIC_R_GAIN_STATUS:
	case DA9055_MIXIN_L_GAIN_STATUS:
	case DA9055_MIXIN_R_GAIN_STATUS:
	case DA9055_ADC_L_GAIN_STATUS:
	case DA9055_ADC_R_GAIN_STATUS:
	case DA9055_DAC_L_GAIN_STATUS:
	case DA9055_DAC_R_GAIN_STATUS:
	case DA9055_HP_L_GAIN_STATUS:
	case DA9055_HP_R_GAIN_STATUS:
	case DA9055_LINE_GAIN_STATUS:
	case DA9055_ALC_CIC_OP_LVL_DATA:
		return true;
	default:
		return false;
	}
}