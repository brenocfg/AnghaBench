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
struct snd_soc_dapm_widget {int id; } ;

/* Variables and functions */
#define  snd_soc_dapm_aif_in 133 
#define  snd_soc_dapm_aif_out 132 
#define  snd_soc_dapm_input 131 
#define  snd_soc_dapm_mixer 130 
#define  snd_soc_dapm_output 129 
#define  snd_soc_dapm_pga 128 

__attribute__((used)) static bool is_sst_dapm_widget(struct snd_soc_dapm_widget *w)
{
	switch (w->id) {
	case snd_soc_dapm_pga:
	case snd_soc_dapm_aif_in:
	case snd_soc_dapm_aif_out:
	case snd_soc_dapm_input:
	case snd_soc_dapm_output:
	case snd_soc_dapm_mixer:
		return true;
	default:
		return false;
	}
}