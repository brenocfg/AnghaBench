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
#define  WM8955_ADDITIONAL_CONTROL_1 156 
#define  WM8955_ADDITIONAL_CONTROL_2 155 
#define  WM8955_ADDITIONAL_CONTROL_3 154 
#define  WM8955_AUDIO_INTERFACE 153 
#define  WM8955_BASS_CONTROL 152 
#define  WM8955_CLOCKING_PLL 151 
#define  WM8955_DAC_CONTROL 150 
#define  WM8955_LEFT_DAC_VOLUME 149 
#define  WM8955_LEFT_OUT_MIX_1 148 
#define  WM8955_LEFT_OUT_MIX_2 147 
#define  WM8955_LOUT1_VOLUME 146 
#define  WM8955_LOUT2_VOLUME 145 
#define  WM8955_MONOOUT_VOLUME 144 
#define  WM8955_MONO_OUT_MIX_1 143 
#define  WM8955_MONO_OUT_MIX_2 142 
#define  WM8955_PLL_CONTROL_1 141 
#define  WM8955_PLL_CONTROL_2 140 
#define  WM8955_PLL_CONTROL_3 139 
#define  WM8955_PLL_CONTROL_4 138 
#define  WM8955_POWER_MANAGEMENT_1 137 
#define  WM8955_POWER_MANAGEMENT_2 136 
#define  WM8955_RESET 135 
#define  WM8955_RIGHT_DAC_VOLUME 134 
#define  WM8955_RIGHT_OUT_MIX_1 133 
#define  WM8955_RIGHT_OUT_MIX_2 132 
#define  WM8955_ROUT1_VOLUME 131 
#define  WM8955_ROUT2_VOLUME 130 
#define  WM8955_SAMPLE_RATE 129 
#define  WM8955_TREBLE_CONTROL 128 

__attribute__((used)) static bool wm8955_writeable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM8955_LOUT1_VOLUME:
	case WM8955_ROUT1_VOLUME:
	case WM8955_DAC_CONTROL:
	case WM8955_AUDIO_INTERFACE:
	case WM8955_SAMPLE_RATE:
	case WM8955_LEFT_DAC_VOLUME:
	case WM8955_RIGHT_DAC_VOLUME:
	case WM8955_BASS_CONTROL:
	case WM8955_TREBLE_CONTROL:
	case WM8955_RESET:
	case WM8955_ADDITIONAL_CONTROL_1:
	case WM8955_ADDITIONAL_CONTROL_2:
	case WM8955_POWER_MANAGEMENT_1:
	case WM8955_POWER_MANAGEMENT_2:
	case WM8955_ADDITIONAL_CONTROL_3:
	case WM8955_LEFT_OUT_MIX_1:
	case WM8955_LEFT_OUT_MIX_2:
	case WM8955_RIGHT_OUT_MIX_1:
	case WM8955_RIGHT_OUT_MIX_2:
	case WM8955_MONO_OUT_MIX_1:
	case WM8955_MONO_OUT_MIX_2:
	case WM8955_LOUT2_VOLUME:
	case WM8955_ROUT2_VOLUME:
	case WM8955_MONOOUT_VOLUME:
	case WM8955_CLOCKING_PLL:
	case WM8955_PLL_CONTROL_1:
	case WM8955_PLL_CONTROL_2:
	case WM8955_PLL_CONTROL_3:
	case WM8955_PLL_CONTROL_4:
		return true;
	default:
		return false;
	}
}