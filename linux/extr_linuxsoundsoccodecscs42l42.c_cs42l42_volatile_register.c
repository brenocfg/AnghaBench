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
#define  CS42L42_ADC_OVFL_STATUS 149 
#define  CS42L42_ASP_RX_STATUS 148 
#define  CS42L42_ASP_TX_STATUS 147 
#define  CS42L42_CODEC_STATUS 146 
#define  CS42L42_DET_INT_STATUS1 145 
#define  CS42L42_DET_INT_STATUS2 144 
#define  CS42L42_DET_STATUS1 143 
#define  CS42L42_DET_STATUS2 142 
#define  CS42L42_DEVID_AB 141 
#define  CS42L42_DEVID_CD 140 
#define  CS42L42_DEVID_E 139 
#define  CS42L42_HS_DET_STATUS 138 
#define  CS42L42_LOAD_DET_DONE 137 
#define  CS42L42_LOAD_DET_RCSTAT 136 
#define  CS42L42_MCLK_STATUS 135 
#define  CS42L42_MIXER_STATUS 134 
#define  CS42L42_PLL_LOCK_STATUS 133 
#define  CS42L42_SRCPL_INT_STATUS 132 
#define  CS42L42_SRC_STATUS 131 
#define  CS42L42_TRSENSE_STATUS 130 
#define  CS42L42_TSRS_PLUG_STATUS 129 
#define  CS42L42_VPMON_STATUS 128 

__attribute__((used)) static bool cs42l42_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS42L42_DEVID_AB:
	case CS42L42_DEVID_CD:
	case CS42L42_DEVID_E:
	case CS42L42_MCLK_STATUS:
	case CS42L42_TRSENSE_STATUS:
	case CS42L42_HS_DET_STATUS:
	case CS42L42_ADC_OVFL_STATUS:
	case CS42L42_MIXER_STATUS:
	case CS42L42_SRC_STATUS:
	case CS42L42_ASP_RX_STATUS:
	case CS42L42_ASP_TX_STATUS:
	case CS42L42_CODEC_STATUS:
	case CS42L42_DET_INT_STATUS1:
	case CS42L42_DET_INT_STATUS2:
	case CS42L42_SRCPL_INT_STATUS:
	case CS42L42_VPMON_STATUS:
	case CS42L42_PLL_LOCK_STATUS:
	case CS42L42_TSRS_PLUG_STATUS:
	case CS42L42_LOAD_DET_RCSTAT:
	case CS42L42_LOAD_DET_DONE:
	case CS42L42_DET_STATUS1:
	case CS42L42_DET_STATUS2:
		return true;
	default:
		return false;
	}
}