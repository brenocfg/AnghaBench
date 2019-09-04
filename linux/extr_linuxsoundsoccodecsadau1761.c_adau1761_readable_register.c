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
#define  ADAU1761_CLK_ENABLE0 151 
#define  ADAU1761_CLK_ENABLE1 150 
#define  ADAU1761_DEJITTER 149 
#define  ADAU1761_DIGMIC_JACKDETECT 148 
#define  ADAU1761_JACK_DETECT_PIN 147 
#define  ADAU1761_LEFT_DIFF_INPUT_VOL 146 
#define  ADAU1761_PLAY_HP_LEFT_VOL 145 
#define  ADAU1761_PLAY_HP_RIGHT_VOL 144 
#define  ADAU1761_PLAY_LINE_LEFT_VOL 143 
#define  ADAU1761_PLAY_LINE_RIGHT_VOL 142 
#define  ADAU1761_PLAY_LR_MIXER_LEFT 141 
#define  ADAU1761_PLAY_LR_MIXER_RIGHT 140 
#define  ADAU1761_PLAY_MIXER_LEFT0 139 
#define  ADAU1761_PLAY_MIXER_LEFT1 138 
#define  ADAU1761_PLAY_MIXER_MONO 137 
#define  ADAU1761_PLAY_MIXER_RIGHT0 136 
#define  ADAU1761_PLAY_MIXER_RIGHT1 135 
#define  ADAU1761_PLAY_MONO_OUTPUT_VOL 134 
#define  ADAU1761_POP_CLICK_SUPPRESS 133 
#define  ADAU1761_REC_MIXER_LEFT0 132 
#define  ADAU1761_REC_MIXER_LEFT1 131 
#define  ADAU1761_REC_MIXER_RIGHT0 130 
#define  ADAU1761_REC_MIXER_RIGHT1 129 
#define  ADAU1761_RIGHT_DIFF_INPUT_VOL 128 
 int adau17x1_readable_register (struct device*,unsigned int) ; 

__attribute__((used)) static bool adau1761_readable_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case ADAU1761_DIGMIC_JACKDETECT:
	case ADAU1761_REC_MIXER_LEFT0:
	case ADAU1761_REC_MIXER_LEFT1:
	case ADAU1761_REC_MIXER_RIGHT0:
	case ADAU1761_REC_MIXER_RIGHT1:
	case ADAU1761_LEFT_DIFF_INPUT_VOL:
	case ADAU1761_RIGHT_DIFF_INPUT_VOL:
	case ADAU1761_PLAY_LR_MIXER_LEFT:
	case ADAU1761_PLAY_MIXER_LEFT0:
	case ADAU1761_PLAY_MIXER_LEFT1:
	case ADAU1761_PLAY_MIXER_RIGHT0:
	case ADAU1761_PLAY_MIXER_RIGHT1:
	case ADAU1761_PLAY_LR_MIXER_RIGHT:
	case ADAU1761_PLAY_MIXER_MONO:
	case ADAU1761_PLAY_HP_LEFT_VOL:
	case ADAU1761_PLAY_HP_RIGHT_VOL:
	case ADAU1761_PLAY_LINE_LEFT_VOL:
	case ADAU1761_PLAY_LINE_RIGHT_VOL:
	case ADAU1761_PLAY_MONO_OUTPUT_VOL:
	case ADAU1761_POP_CLICK_SUPPRESS:
	case ADAU1761_JACK_DETECT_PIN:
	case ADAU1761_DEJITTER:
	case ADAU1761_CLK_ENABLE0:
	case ADAU1761_CLK_ENABLE1:
		return true;
	default:
		break;
	}

	return adau17x1_readable_register(dev, reg);
}