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
#define  RT1308_BQ_PARA_UPDATE 174 
#define  RT1308_BQ_SET 173 
#define  RT1308_CAL_OFFSET_DAC_L 172 
#define  RT1308_CAL_OFFSET_DAC_PBTL 171 
#define  RT1308_CAL_OFFSET_DAC_R 170 
#define  RT1308_CAL_OFFSET_PWM_L 169 
#define  RT1308_CAL_OFFSET_PWM_R 168 
#define  RT1308_CAL_PWM_VOS_ADC_L 167 
#define  RT1308_CAL_PWM_VOS_ADC_R 166 
#define  RT1308_CLK_2 165 
#define  RT1308_CLK_DET 164 
#define  RT1308_DAC_BUF 163 
#define  RT1308_DAC_SET 162 
#define  RT1308_DC_CAL_1 161 
#define  RT1308_DC_DET 160 
#define  RT1308_DUMMY_REG 159 
#define  RT1308_EFUSE_1 158 
#define  RT1308_EFUSE_DATA_0_LSB 157 
#define  RT1308_EFUSE_DATA_0_MSB 156 
#define  RT1308_EFUSE_DATA_1_LSB 155 
#define  RT1308_EFUSE_DATA_1_MSB 154 
#define  RT1308_EFUSE_DATA_2_LSB 153 
#define  RT1308_EFUSE_DATA_2_MSB 152 
#define  RT1308_EFUSE_DATA_3_LSB 151 
#define  RT1308_EFUSE_DATA_3_MSB 150 
#define  RT1308_EFUSE_READ_ADC_L 149 
#define  RT1308_EFUSE_READ_ADC_PBTL 148 
#define  RT1308_EFUSE_READ_ADC_R 147 
#define  RT1308_EFUSE_READ_DEV 146 
#define  RT1308_EFUSE_READ_PVDD_L 145 
#define  RT1308_EFUSE_READ_PVDD_PTBL 144 
#define  RT1308_EFUSE_READ_PVDD_R 143 
#define  RT1308_EFUSE_READ_R0 142 
#define  RT1308_EFUSE_RESERVE 141 
#define  RT1308_EFUSE_STATUS_1 140 
#define  RT1308_EFUSE_STATUS_2 139 
#define  RT1308_MBIAS 138 
#define  RT1308_POWER_INT 137 
#define  RT1308_POWER_STATUS 136 
#define  RT1308_PVDD_OFFSET_CTL 135 
#define  RT1308_RESET 134 
#define  RT1308_RESET_N 133 
#define  RT1308_SDW_REG_RDATA 132 
#define  RT1308_SIL_DET 131 
#define  RT1308_SINE_TONE_GEN_2 130 
#define  RT1308_VEN_DEV_ID 129 
#define  RT1308_VERSION_ID 128 

__attribute__((used)) static bool rt1308_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case RT1308_RESET:
	case RT1308_RESET_N:
	case RT1308_CLK_2:
	case RT1308_SIL_DET:
	case RT1308_CLK_DET:
	case RT1308_DC_DET:
	case RT1308_DAC_SET:
	case RT1308_DAC_BUF:
	case RT1308_SDW_REG_RDATA:
	case RT1308_DC_CAL_1:
	case RT1308_PVDD_OFFSET_CTL:
	case RT1308_CAL_OFFSET_DAC_PBTL:
	case RT1308_CAL_OFFSET_DAC_L:
	case RT1308_CAL_OFFSET_DAC_R:
	case RT1308_CAL_OFFSET_PWM_L:
	case RT1308_CAL_OFFSET_PWM_R:
	case RT1308_CAL_PWM_VOS_ADC_L:
	case RT1308_CAL_PWM_VOS_ADC_R:
	case RT1308_MBIAS:
	case RT1308_POWER_STATUS:
	case RT1308_POWER_INT:
	case RT1308_SINE_TONE_GEN_2:
	case RT1308_BQ_SET:
	case RT1308_BQ_PARA_UPDATE:
	case RT1308_VEN_DEV_ID:
	case RT1308_VERSION_ID:
	case RT1308_EFUSE_1:
	case RT1308_EFUSE_READ_PVDD_L:
	case RT1308_EFUSE_READ_PVDD_R:
	case RT1308_EFUSE_READ_PVDD_PTBL:
	case RT1308_EFUSE_READ_DEV:
	case RT1308_EFUSE_READ_R0:
	case RT1308_EFUSE_READ_ADC_L:
	case RT1308_EFUSE_READ_ADC_R:
	case RT1308_EFUSE_READ_ADC_PBTL:
	case RT1308_EFUSE_RESERVE:
	case RT1308_EFUSE_DATA_0_MSB:
	case RT1308_EFUSE_DATA_0_LSB:
	case RT1308_EFUSE_DATA_1_MSB:
	case RT1308_EFUSE_DATA_1_LSB:
	case RT1308_EFUSE_DATA_2_MSB:
	case RT1308_EFUSE_DATA_2_LSB:
	case RT1308_EFUSE_DATA_3_MSB:
	case RT1308_EFUSE_DATA_3_LSB:
	case RT1308_EFUSE_STATUS_1:
	case RT1308_EFUSE_STATUS_2:
	case RT1308_DUMMY_REG:
		return true;
	default:
		return false;
	}
}