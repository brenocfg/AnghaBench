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
struct gb_audio_widget {int type; int ncontrols; } ;

/* Variables and functions */
 int EINVAL ; 
#define  snd_soc_dapm_hp 134 
#define  snd_soc_dapm_input 133 
#define  snd_soc_dapm_mic 132 
#define  snd_soc_dapm_mux 131 
#define  snd_soc_dapm_output 130 
#define  snd_soc_dapm_spk 129 
#define  snd_soc_dapm_switch 128 

__attribute__((used)) static int gbaudio_validate_kcontrol_count(struct gb_audio_widget *w)
{
	int ret = 0;

	switch (w->type) {
	case snd_soc_dapm_spk:
	case snd_soc_dapm_hp:
	case snd_soc_dapm_mic:
	case snd_soc_dapm_output:
	case snd_soc_dapm_input:
		if (w->ncontrols)
			ret = -EINVAL;
		break;
	case snd_soc_dapm_switch:
	case snd_soc_dapm_mux:
		if (w->ncontrols != 1)
			ret = -EINVAL;
		break;
	default:
		break;
	}

	return ret;
}