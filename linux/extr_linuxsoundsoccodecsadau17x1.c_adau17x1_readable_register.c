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
#define  ADAU17X1_ADC_CONTROL 151 
#define  ADAU17X1_CLOCK_CONTROL 150 
#define  ADAU17X1_CONTROL_PORT_PAD0 149 
#define  ADAU17X1_CONTROL_PORT_PAD1 148 
#define  ADAU17X1_CONVERTER0 147 
#define  ADAU17X1_CONVERTER1 146 
#define  ADAU17X1_DAC_CONTROL0 145 
#define  ADAU17X1_DAC_CONTROL1 144 
#define  ADAU17X1_DAC_CONTROL2 143 
#define  ADAU17X1_DSP_ENABLE 142 
#define  ADAU17X1_DSP_RUN 141 
#define  ADAU17X1_DSP_SAMPLING_RATE 140 
#define  ADAU17X1_LEFT_INPUT_DIGITAL_VOL 139 
#define  ADAU17X1_MICBIAS 138 
#define  ADAU17X1_PLAY_POWER_MGMT 137 
#define  ADAU17X1_PLL_CONTROL 136 
#define  ADAU17X1_REC_POWER_MGMT 135 
#define  ADAU17X1_RIGHT_INPUT_DIGITAL_VOL 134 
#define  ADAU17X1_SERIAL_INPUT_ROUTE 133 
#define  ADAU17X1_SERIAL_OUTPUT_ROUTE 132 
#define  ADAU17X1_SERIAL_PORT0 131 
#define  ADAU17X1_SERIAL_PORT1 130 
#define  ADAU17X1_SERIAL_PORT_PAD 129 
#define  ADAU17X1_SERIAL_SAMPLING_RATE 128 

bool adau17x1_readable_register(struct device *dev, unsigned int reg)
{
	/* SigmaDSP parameter memory */
	if (reg < 0x400)
		return true;

	switch (reg) {
	case ADAU17X1_CLOCK_CONTROL:
	case ADAU17X1_PLL_CONTROL:
	case ADAU17X1_REC_POWER_MGMT:
	case ADAU17X1_MICBIAS:
	case ADAU17X1_SERIAL_PORT0:
	case ADAU17X1_SERIAL_PORT1:
	case ADAU17X1_CONVERTER0:
	case ADAU17X1_CONVERTER1:
	case ADAU17X1_LEFT_INPUT_DIGITAL_VOL:
	case ADAU17X1_RIGHT_INPUT_DIGITAL_VOL:
	case ADAU17X1_ADC_CONTROL:
	case ADAU17X1_PLAY_POWER_MGMT:
	case ADAU17X1_DAC_CONTROL0:
	case ADAU17X1_DAC_CONTROL1:
	case ADAU17X1_DAC_CONTROL2:
	case ADAU17X1_SERIAL_PORT_PAD:
	case ADAU17X1_CONTROL_PORT_PAD0:
	case ADAU17X1_CONTROL_PORT_PAD1:
	case ADAU17X1_DSP_SAMPLING_RATE:
	case ADAU17X1_SERIAL_INPUT_ROUTE:
	case ADAU17X1_SERIAL_OUTPUT_ROUTE:
	case ADAU17X1_DSP_ENABLE:
	case ADAU17X1_DSP_RUN:
	case ADAU17X1_SERIAL_SAMPLING_RATE:
		return true;
	default:
		break;
	}
	return false;
}