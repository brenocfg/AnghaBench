#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_3__ {unsigned int window_start; unsigned int window_len; unsigned int range_min; unsigned int range_max; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
#define  RT5670_ADC_EQ_CTRL1 153 
#define  RT5670_ALC_CTRL_1 152 
#define  RT5670_ASRC_5 151 
#define  RT5670_A_JD_CTRL1 150 
#define  RT5670_A_JD_CTRL2 149 
#define  RT5670_CJ_CTRL1 148 
#define  RT5670_CJ_CTRL2 147 
#define  RT5670_CJ_CTRL3 146 
#define  RT5670_DSP_CTRL1 145 
#define  RT5670_DSP_CTRL2 144 
#define  RT5670_DSP_CTRL3 143 
#define  RT5670_DSP_CTRL4 142 
#define  RT5670_DSP_CTRL5 141 
#define  RT5670_EQ_CTRL1 140 
#define  RT5670_IL_CMD 139 
#define  RT5670_INT_IRQ_ST 138 
#define  RT5670_IRQ_CTRL2 137 
#define  RT5670_PDM1_DATA_CTRL4 136 
#define  RT5670_PDM2_DATA_CTRL4 135 
#define  RT5670_PDM_DATA_CTRL1 134 
#define  RT5670_PRIV_DATA 133 
#define  RT5670_RESET 132 
#define  RT5670_VAD_CTRL5 131 
#define  RT5670_VENDOR_ID 130 
#define  RT5670_VENDOR_ID1 129 
#define  RT5670_VENDOR_ID2 128 
 TYPE_1__* rt5670_ranges ; 

__attribute__((used)) static bool rt5670_volatile_register(struct device *dev, unsigned int reg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(rt5670_ranges); i++) {
		if ((reg >= rt5670_ranges[i].window_start &&
		     reg <= rt5670_ranges[i].window_start +
		     rt5670_ranges[i].window_len) ||
		    (reg >= rt5670_ranges[i].range_min &&
		     reg <= rt5670_ranges[i].range_max)) {
			return true;
		}
	}

	switch (reg) {
	case RT5670_RESET:
	case RT5670_PDM_DATA_CTRL1:
	case RT5670_PDM1_DATA_CTRL4:
	case RT5670_PDM2_DATA_CTRL4:
	case RT5670_PRIV_DATA:
	case RT5670_ASRC_5:
	case RT5670_CJ_CTRL1:
	case RT5670_CJ_CTRL2:
	case RT5670_CJ_CTRL3:
	case RT5670_A_JD_CTRL1:
	case RT5670_A_JD_CTRL2:
	case RT5670_VAD_CTRL5:
	case RT5670_ADC_EQ_CTRL1:
	case RT5670_EQ_CTRL1:
	case RT5670_ALC_CTRL_1:
	case RT5670_IRQ_CTRL2:
	case RT5670_INT_IRQ_ST:
	case RT5670_IL_CMD:
	case RT5670_DSP_CTRL1:
	case RT5670_DSP_CTRL2:
	case RT5670_DSP_CTRL3:
	case RT5670_DSP_CTRL4:
	case RT5670_DSP_CTRL5:
	case RT5670_VENDOR_ID:
	case RT5670_VENDOR_ID1:
	case RT5670_VENDOR_ID2:
		return true;
	default:
		return false;
	}
}