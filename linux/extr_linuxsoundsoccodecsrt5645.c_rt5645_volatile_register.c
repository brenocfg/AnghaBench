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
struct TYPE_3__ {unsigned int range_min; unsigned int range_max; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
#define  RT5645_ADC_EQ_CTRL1 145 
#define  RT5645_ALC_CTRL_1 144 
#define  RT5645_A_JD_CTRL1 143 
#define  RT5645_EQ_CTRL1 142 
#define  RT5645_IL_CMD 141 
#define  RT5645_IN1_CTRL1 140 
#define  RT5645_IN1_CTRL2 139 
#define  RT5645_IN1_CTRL3 138 
#define  RT5645_INT_IRQ_ST 137 
#define  RT5645_IRQ_CTRL2 136 
#define  RT5645_IRQ_CTRL3 135 
#define  RT5645_PRIV_DATA 134 
#define  RT5645_PRIV_INDEX 133 
#define  RT5645_RESET 132 
#define  RT5645_VENDOR_ID 131 
#define  RT5645_VENDOR_ID1 130 
#define  RT5645_VENDOR_ID2 129 
#define  RT5650_4BTN_IL_CMD1 128 
 TYPE_1__* rt5645_ranges ; 

__attribute__((used)) static bool rt5645_volatile_register(struct device *dev, unsigned int reg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(rt5645_ranges); i++) {
		if (reg >= rt5645_ranges[i].range_min &&
			reg <= rt5645_ranges[i].range_max) {
			return true;
		}
	}

	switch (reg) {
	case RT5645_RESET:
	case RT5645_PRIV_INDEX:
	case RT5645_PRIV_DATA:
	case RT5645_IN1_CTRL1:
	case RT5645_IN1_CTRL2:
	case RT5645_IN1_CTRL3:
	case RT5645_A_JD_CTRL1:
	case RT5645_ADC_EQ_CTRL1:
	case RT5645_EQ_CTRL1:
	case RT5645_ALC_CTRL_1:
	case RT5645_IRQ_CTRL2:
	case RT5645_IRQ_CTRL3:
	case RT5645_INT_IRQ_ST:
	case RT5645_IL_CMD:
	case RT5650_4BTN_IL_CMD1:
	case RT5645_VENDOR_ID:
	case RT5645_VENDOR_ID1:
	case RT5645_VENDOR_ID2:
		return true;
	default:
		return false;
	}
}