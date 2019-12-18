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
#define  RT5663_ADC_EQ_1 173 
#define  RT5663_ALC_BK_GAIN 172 
#define  RT5663_A_JD_CTRL 171 
#define  RT5663_CBJ_TYPE_2 170 
#define  RT5663_GPIO_STA2 169 
#define  RT5663_HP_CALIB_1 168 
#define  RT5663_HP_CALIB_10 167 
#define  RT5663_HP_CALIB_ST1 166 
#define  RT5663_HP_CALIB_ST10 165 
#define  RT5663_HP_CALIB_ST11 164 
#define  RT5663_HP_CALIB_ST4 163 
#define  RT5663_HP_CALIB_ST5 162 
#define  RT5663_HP_CALIB_ST6 161 
#define  RT5663_HP_CALIB_ST7 160 
#define  RT5663_HP_CALIB_ST8 159 
#define  RT5663_HP_CALIB_ST9 158 
#define  RT5663_HP_IMP_SEN_10 157 
#define  RT5663_HP_IMP_SEN_2 156 
#define  RT5663_HP_IMP_SEN_3 155 
#define  RT5663_HP_IMP_SEN_4 154 
#define  RT5663_IL_CMD_1 153 
#define  RT5663_IL_CMD_5 152 
#define  RT5663_INT_ST_1 151 
#define  RT5663_JD_CTRL2 150 
#define  RT5663_MICBIAS_1 149 
#define  RT5663_MONOL_SIL_DET 148 
#define  RT5663_MONOR_SIL_DET 147 
#define  RT5663_MONO_AMP_CAL_ST1 146 
#define  RT5663_MONO_AMP_CAL_ST2 145 
#define  RT5663_MONO_AMP_CAL_ST3 144 
#define  RT5663_MONO_AMP_CAL_ST4 143 
#define  RT5663_MONO_DYNA_6 142 
#define  RT5663_PDM_I2C_DATA_CTL1 141 
#define  RT5663_PDM_I2C_DATA_CTL4 140 
#define  RT5663_PDM_OUT_CTL 139 
#define  RT5663_PLL_2 138 
#define  RT5663_RESET 137 
#define  RT5663_STO1_SIL_DET 136 
#define  RT5663_STO2_DAC_SIL 135 
#define  RT5663_STO_DRE_1 134 
#define  RT5663_STO_DRE_5 133 
#define  RT5663_STO_DRE_6 132 
#define  RT5663_STO_DRE_7 131 
#define  RT5663_VENDOR_ID 130 
#define  RT5663_VENDOR_ID_1 129 
#define  RT5663_VENDOR_ID_2 128 

__attribute__((used)) static bool rt5663_v2_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case RT5663_RESET:
	case RT5663_CBJ_TYPE_2:
	case RT5663_PDM_OUT_CTL:
	case RT5663_PDM_I2C_DATA_CTL1:
	case RT5663_PDM_I2C_DATA_CTL4:
	case RT5663_ALC_BK_GAIN:
	case RT5663_PLL_2:
	case RT5663_MICBIAS_1:
	case RT5663_ADC_EQ_1:
	case RT5663_INT_ST_1:
	case RT5663_GPIO_STA2:
	case RT5663_IL_CMD_1:
	case RT5663_IL_CMD_5:
	case RT5663_A_JD_CTRL:
	case RT5663_JD_CTRL2:
	case RT5663_VENDOR_ID:
	case RT5663_VENDOR_ID_1:
	case RT5663_VENDOR_ID_2:
	case RT5663_STO_DRE_1:
	case RT5663_STO_DRE_5:
	case RT5663_STO_DRE_6:
	case RT5663_STO_DRE_7:
	case RT5663_MONO_DYNA_6:
	case RT5663_STO1_SIL_DET:
	case RT5663_MONOL_SIL_DET:
	case RT5663_MONOR_SIL_DET:
	case RT5663_STO2_DAC_SIL:
	case RT5663_MONO_AMP_CAL_ST1:
	case RT5663_MONO_AMP_CAL_ST2:
	case RT5663_MONO_AMP_CAL_ST3:
	case RT5663_MONO_AMP_CAL_ST4:
	case RT5663_HP_IMP_SEN_2:
	case RT5663_HP_IMP_SEN_3:
	case RT5663_HP_IMP_SEN_4:
	case RT5663_HP_IMP_SEN_10:
	case RT5663_HP_CALIB_1:
	case RT5663_HP_CALIB_10:
	case RT5663_HP_CALIB_ST1:
	case RT5663_HP_CALIB_ST4:
	case RT5663_HP_CALIB_ST5:
	case RT5663_HP_CALIB_ST6:
	case RT5663_HP_CALIB_ST7:
	case RT5663_HP_CALIB_ST8:
	case RT5663_HP_CALIB_ST9:
	case RT5663_HP_CALIB_ST10:
	case RT5663_HP_CALIB_ST11:
		return true;
	default:
		return false;
	}
}