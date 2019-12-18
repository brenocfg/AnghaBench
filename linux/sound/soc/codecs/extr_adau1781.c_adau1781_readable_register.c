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
#define  ADAU1781_BEEP_ZC 140 
#define  ADAU1781_DEJITTER 139 
#define  ADAU1781_DIG_PWDN0 138 
#define  ADAU1781_DIG_PWDN1 137 
#define  ADAU1781_DMIC_BEEP_CTRL 136 
#define  ADAU1781_LEFT_LINEOUT 135 
#define  ADAU1781_LEFT_PGA 134 
#define  ADAU1781_LEFT_PLAYBACK_MIXER 133 
#define  ADAU1781_MONO_PLAYBACK_MIXER 132 
#define  ADAU1781_RIGHT_LINEOUT 131 
#define  ADAU1781_RIGHT_PGA 130 
#define  ADAU1781_RIGHT_PLAYBACK_MIXER 129 
#define  ADAU1781_SPEAKER 128 
 int adau17x1_readable_register (struct device*,unsigned int) ; 

__attribute__((used)) static bool adau1781_readable_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case ADAU1781_DMIC_BEEP_CTRL:
	case ADAU1781_LEFT_PGA:
	case ADAU1781_RIGHT_PGA:
	case ADAU1781_LEFT_PLAYBACK_MIXER:
	case ADAU1781_RIGHT_PLAYBACK_MIXER:
	case ADAU1781_MONO_PLAYBACK_MIXER:
	case ADAU1781_LEFT_LINEOUT:
	case ADAU1781_RIGHT_LINEOUT:
	case ADAU1781_SPEAKER:
	case ADAU1781_BEEP_ZC:
	case ADAU1781_DEJITTER:
	case ADAU1781_DIG_PWDN0:
	case ADAU1781_DIG_PWDN1:
		return true;
	default:
		break;
	}

	return adau17x1_readable_register(dev, reg);
}