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
#define  DA7219_ACCDET_CONFIG_8 148 
#define  DA7219_ACCDET_IRQ_EVENT_A 147 
#define  DA7219_ACCDET_IRQ_EVENT_B 146 
#define  DA7219_ACCDET_STATUS_A 145 
#define  DA7219_ACCDET_STATUS_B 144 
#define  DA7219_ADC_L_GAIN_STATUS 143 
#define  DA7219_ALC_CTRL1 142 
#define  DA7219_ALC_OFFSET_AUTO_M_L 141 
#define  DA7219_ALC_OFFSET_AUTO_U_L 140 
#define  DA7219_CIF_CTRL 139 
#define  DA7219_DAC_L_GAIN_STATUS 138 
#define  DA7219_DAC_R_GAIN_STATUS 137 
#define  DA7219_HP_L_GAIN_STATUS 136 
#define  DA7219_HP_R_GAIN_STATUS 135 
#define  DA7219_MIC_1_GAIN_STATUS 134 
#define  DA7219_MIXIN_L_GAIN_STATUS 133 
#define  DA7219_PLL_SRM_STS 132 
#define  DA7219_SYSTEM_MODES_INPUT 131 
#define  DA7219_SYSTEM_MODES_OUTPUT 130 
#define  DA7219_SYSTEM_STATUS 129 
#define  DA7219_TONE_GEN_CFG1 128 

__attribute__((used)) static bool da7219_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case DA7219_MIC_1_GAIN_STATUS:
	case DA7219_MIXIN_L_GAIN_STATUS:
	case DA7219_ADC_L_GAIN_STATUS:
	case DA7219_DAC_L_GAIN_STATUS:
	case DA7219_DAC_R_GAIN_STATUS:
	case DA7219_HP_L_GAIN_STATUS:
	case DA7219_HP_R_GAIN_STATUS:
	case DA7219_CIF_CTRL:
	case DA7219_PLL_SRM_STS:
	case DA7219_ALC_CTRL1:
	case DA7219_SYSTEM_MODES_INPUT:
	case DA7219_SYSTEM_MODES_OUTPUT:
	case DA7219_ALC_OFFSET_AUTO_M_L:
	case DA7219_ALC_OFFSET_AUTO_U_L:
	case DA7219_TONE_GEN_CFG1:
	case DA7219_ACCDET_STATUS_A:
	case DA7219_ACCDET_STATUS_B:
	case DA7219_ACCDET_IRQ_EVENT_A:
	case DA7219_ACCDET_IRQ_EVENT_B:
	case DA7219_ACCDET_CONFIG_8:
	case DA7219_SYSTEM_STATUS:
		return true;
	default:
		return false;
	}
}