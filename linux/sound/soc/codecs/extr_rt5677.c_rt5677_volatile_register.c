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
#define  RT5677_ADC_EQ_CTRL1 155 
#define  RT5677_ASRC_22 154 
#define  RT5677_ASRC_23 153 
#define  RT5677_DSP_INB1_SRC_CTRL4 152 
#define  RT5677_DSP_INB2_SRC_CTRL4 151 
#define  RT5677_DSP_INB3_SRC_CTRL4 150 
#define  RT5677_DSP_OUTB1_SRC_CTRL4 149 
#define  RT5677_DSP_OUTB2_SRC_CTRL4 148 
#define  RT5677_EQ_CTRL1 147 
#define  RT5677_GPIO_ST 146 
#define  RT5677_HAP_GENE_CTRL2 145 
#define  RT5677_I2C_MASTER_CTRL1 144 
#define  RT5677_I2C_MASTER_CTRL7 143 
#define  RT5677_I2C_MASTER_CTRL8 142 
#define  RT5677_IRQ_CTRL1 141 
#define  RT5677_IRQ_CTRL2 140 
#define  RT5677_PDM1_DATA_CTRL4 139 
#define  RT5677_PDM2_DATA_CTRL4 138 
#define  RT5677_PDM_DATA_CTRL1 137 
#define  RT5677_PDM_DATA_CTRL2 136 
#define  RT5677_PRIV_DATA 135 
#define  RT5677_PWR_DSP_ST 134 
#define  RT5677_RESET 133 
#define  RT5677_SLIMBUS_PARAM 132 
#define  RT5677_VAD_CTRL5 131 
#define  RT5677_VENDOR_ID 130 
#define  RT5677_VENDOR_ID1 129 
#define  RT5677_VENDOR_ID2 128 
 TYPE_1__* rt5677_ranges ; 

__attribute__((used)) static bool rt5677_volatile_register(struct device *dev, unsigned int reg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(rt5677_ranges); i++) {
		if (reg >= rt5677_ranges[i].range_min &&
			reg <= rt5677_ranges[i].range_max) {
			return true;
		}
	}

	switch (reg) {
	case RT5677_RESET:
	case RT5677_SLIMBUS_PARAM:
	case RT5677_PDM_DATA_CTRL1:
	case RT5677_PDM_DATA_CTRL2:
	case RT5677_PDM1_DATA_CTRL4:
	case RT5677_PDM2_DATA_CTRL4:
	case RT5677_I2C_MASTER_CTRL1:
	case RT5677_I2C_MASTER_CTRL7:
	case RT5677_I2C_MASTER_CTRL8:
	case RT5677_HAP_GENE_CTRL2:
	case RT5677_PWR_DSP_ST:
	case RT5677_PRIV_DATA:
	case RT5677_ASRC_22:
	case RT5677_ASRC_23:
	case RT5677_VAD_CTRL5:
	case RT5677_ADC_EQ_CTRL1:
	case RT5677_EQ_CTRL1:
	case RT5677_IRQ_CTRL1:
	case RT5677_IRQ_CTRL2:
	case RT5677_GPIO_ST:
	case RT5677_DSP_INB1_SRC_CTRL4:
	case RT5677_DSP_INB2_SRC_CTRL4:
	case RT5677_DSP_INB3_SRC_CTRL4:
	case RT5677_DSP_OUTB1_SRC_CTRL4:
	case RT5677_DSP_OUTB2_SRC_CTRL4:
	case RT5677_VENDOR_ID:
	case RT5677_VENDOR_ID1:
	case RT5677_VENDOR_ID2:
		return true;
	default:
		return false;
	}
}