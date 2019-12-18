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
#define  CS42L51_ADCA_ATT 158 
#define  CS42L51_ADCA_VOL 157 
#define  CS42L51_ADCB_ATT 156 
#define  CS42L51_ADCB_VOL 155 
#define  CS42L51_ADC_CTL 154 
#define  CS42L51_ADC_INPUT 153 
#define  CS42L51_ALC_EN 152 
#define  CS42L51_ALC_PGA_CTL 151 
#define  CS42L51_ALC_PGB_CTL 150 
#define  CS42L51_ALC_REL 149 
#define  CS42L51_ALC_THRES 148 
#define  CS42L51_AOUTA_VOL 147 
#define  CS42L51_AOUTB_VOL 146 
#define  CS42L51_BEEP_CONF 145 
#define  CS42L51_BEEP_FREQ 144 
#define  CS42L51_BEEP_VOL 143 
#define  CS42L51_CHARGE_FREQ 142 
#define  CS42L51_DAC_CTL 141 
#define  CS42L51_DAC_OUT_CTL 140 
#define  CS42L51_INTF_CTL 139 
#define  CS42L51_LIMIT_ATT 138 
#define  CS42L51_LIMIT_REL 137 
#define  CS42L51_LIMIT_THRES_DIS 136 
#define  CS42L51_MIC_CTL 135 
#define  CS42L51_MIC_POWER_CTL 134 
#define  CS42L51_NOISE_CONF 133 
#define  CS42L51_PCMA_VOL 132 
#define  CS42L51_PCMB_VOL 131 
#define  CS42L51_PCM_MIXER 130 
#define  CS42L51_POWER_CTL1 129 
#define  CS42L51_TONE_CTL 128 

__attribute__((used)) static bool cs42l51_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS42L51_POWER_CTL1:
	case CS42L51_MIC_POWER_CTL:
	case CS42L51_INTF_CTL:
	case CS42L51_MIC_CTL:
	case CS42L51_ADC_CTL:
	case CS42L51_ADC_INPUT:
	case CS42L51_DAC_OUT_CTL:
	case CS42L51_DAC_CTL:
	case CS42L51_ALC_PGA_CTL:
	case CS42L51_ALC_PGB_CTL:
	case CS42L51_ADCA_ATT:
	case CS42L51_ADCB_ATT:
	case CS42L51_ADCA_VOL:
	case CS42L51_ADCB_VOL:
	case CS42L51_PCMA_VOL:
	case CS42L51_PCMB_VOL:
	case CS42L51_BEEP_FREQ:
	case CS42L51_BEEP_VOL:
	case CS42L51_BEEP_CONF:
	case CS42L51_TONE_CTL:
	case CS42L51_AOUTA_VOL:
	case CS42L51_AOUTB_VOL:
	case CS42L51_PCM_MIXER:
	case CS42L51_LIMIT_THRES_DIS:
	case CS42L51_LIMIT_REL:
	case CS42L51_LIMIT_ATT:
	case CS42L51_ALC_EN:
	case CS42L51_ALC_REL:
	case CS42L51_ALC_THRES:
	case CS42L51_NOISE_CONF:
	case CS42L51_CHARGE_FREQ:
		return true;
	default:
		return false;
	}
}