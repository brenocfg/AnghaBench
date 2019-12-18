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
#define  DA7213_ADC_L_GAIN_STATUS 148 
#define  DA7213_ADC_R_GAIN_STATUS 147 
#define  DA7213_ALC_CIC_OP_LVL_DATA 146 
#define  DA7213_ALC_CTRL1 145 
#define  DA7213_ALC_OFFSET_AUTO_M_L 144 
#define  DA7213_ALC_OFFSET_AUTO_M_R 143 
#define  DA7213_ALC_OFFSET_AUTO_U_L 142 
#define  DA7213_ALC_OFFSET_AUTO_U_R 141 
#define  DA7213_AUX_L_GAIN_STATUS 140 
#define  DA7213_AUX_R_GAIN_STATUS 139 
#define  DA7213_DAC_L_GAIN_STATUS 138 
#define  DA7213_DAC_R_GAIN_STATUS 137 
#define  DA7213_HP_L_GAIN_STATUS 136 
#define  DA7213_HP_R_GAIN_STATUS 135 
#define  DA7213_LINE_GAIN_STATUS 134 
#define  DA7213_MIC_1_GAIN_STATUS 133 
#define  DA7213_MIC_2_GAIN_STATUS 132 
#define  DA7213_MIXIN_L_GAIN_STATUS 131 
#define  DA7213_MIXIN_R_GAIN_STATUS 130 
#define  DA7213_PLL_STATUS 129 
#define  DA7213_STATUS1 128 

__attribute__((used)) static bool da7213_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case DA7213_STATUS1:
	case DA7213_PLL_STATUS:
	case DA7213_AUX_L_GAIN_STATUS:
	case DA7213_AUX_R_GAIN_STATUS:
	case DA7213_MIC_1_GAIN_STATUS:
	case DA7213_MIC_2_GAIN_STATUS:
	case DA7213_MIXIN_L_GAIN_STATUS:
	case DA7213_MIXIN_R_GAIN_STATUS:
	case DA7213_ADC_L_GAIN_STATUS:
	case DA7213_ADC_R_GAIN_STATUS:
	case DA7213_DAC_L_GAIN_STATUS:
	case DA7213_DAC_R_GAIN_STATUS:
	case DA7213_HP_L_GAIN_STATUS:
	case DA7213_HP_R_GAIN_STATUS:
	case DA7213_LINE_GAIN_STATUS:
	case DA7213_ALC_CTRL1:
	case DA7213_ALC_OFFSET_AUTO_M_L:
	case DA7213_ALC_OFFSET_AUTO_U_L:
	case DA7213_ALC_OFFSET_AUTO_M_R:
	case DA7213_ALC_OFFSET_AUTO_U_R:
	case DA7213_ALC_CIC_OP_LVL_DATA:
		return true;
	default:
		return false;
	}
}