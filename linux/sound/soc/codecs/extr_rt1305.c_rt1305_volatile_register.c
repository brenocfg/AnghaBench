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
#define  RT1305_BIQUAD_SET_1 160 
#define  RT1305_BIQUAD_SET_2 159 
#define  RT1305_CLOCK_DETECT 158 
#define  RT1305_DAC_OFFSET_1 157 
#define  RT1305_DAC_OFFSET_10 156 
#define  RT1305_DAC_OFFSET_11 155 
#define  RT1305_DAC_OFFSET_2 154 
#define  RT1305_DAC_OFFSET_3 153 
#define  RT1305_DAC_OFFSET_4 152 
#define  RT1305_DAC_OFFSET_5 151 
#define  RT1305_DAC_OFFSET_6 150 
#define  RT1305_DAC_OFFSET_7 149 
#define  RT1305_DAC_OFFSET_8 148 
#define  RT1305_DAC_OFFSET_9 147 
#define  RT1305_DC_CALIB_1 146 
#define  RT1305_DC_CALIB_3 145 
#define  RT1305_DEVICE_ID 144 
#define  RT1305_EFUSE_1 143 
#define  RT1305_EFUSE_3 142 
#define  RT1305_EQ_SET_2 141 
#define  RT1305_POWER_CTRL_2 140 
#define  RT1305_RESET 139 
#define  RT1305_SILENCE_DETECT 138 
#define  RT1305_SPDIF_IN_SET_1 137 
#define  RT1305_SPDIF_IN_SET_2 136 
#define  RT1305_SPDIF_IN_SET_3 135 
#define  RT1305_SPK_DC_DETECT_1 134 
#define  RT1305_SPK_TEMP_PROTECTION_0 133 
#define  RT1305_SPK_TEMP_PROTECTION_2 132 
#define  RT1305_TRIM_1 131 
#define  RT1305_TRIM_2 130 
#define  RT1305_VENDOR_ID 129 
#define  RT1305_VERSION_ID 128 
 TYPE_1__* rt1305_ranges ; 

__attribute__((used)) static bool rt1305_volatile_register(struct device *dev, unsigned int reg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(rt1305_ranges); i++) {
		if (reg >= rt1305_ranges[i].range_min &&
			reg <= rt1305_ranges[i].range_max) {
			return true;
		}
	}

	switch (reg) {
	case RT1305_RESET:
	case RT1305_SPDIF_IN_SET_1:
	case RT1305_SPDIF_IN_SET_2:
	case RT1305_SPDIF_IN_SET_3:
	case RT1305_POWER_CTRL_2:
	case RT1305_CLOCK_DETECT:
	case RT1305_BIQUAD_SET_1:
	case RT1305_BIQUAD_SET_2:
	case RT1305_EQ_SET_2:
	case RT1305_SPK_TEMP_PROTECTION_0:
	case RT1305_SPK_TEMP_PROTECTION_2:
	case RT1305_SPK_DC_DETECT_1:
	case RT1305_SILENCE_DETECT:
	case RT1305_VERSION_ID:
	case RT1305_VENDOR_ID:
	case RT1305_DEVICE_ID:
	case RT1305_EFUSE_1:
	case RT1305_EFUSE_3:
	case RT1305_DC_CALIB_1:
	case RT1305_DC_CALIB_3:
	case RT1305_DAC_OFFSET_1:
	case RT1305_DAC_OFFSET_2:
	case RT1305_DAC_OFFSET_3:
	case RT1305_DAC_OFFSET_4:
	case RT1305_DAC_OFFSET_5:
	case RT1305_DAC_OFFSET_6:
	case RT1305_DAC_OFFSET_7:
	case RT1305_DAC_OFFSET_8:
	case RT1305_DAC_OFFSET_9:
	case RT1305_DAC_OFFSET_10:
	case RT1305_DAC_OFFSET_11:
	case RT1305_TRIM_1:
	case RT1305_TRIM_2:
		return true;

	default:
		return false;
	}
}