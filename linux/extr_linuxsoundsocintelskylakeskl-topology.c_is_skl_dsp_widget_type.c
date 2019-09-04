#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_widget {int id; TYPE_1__* dapm; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
#define  snd_soc_dapm_aif_in 135 
#define  snd_soc_dapm_aif_out 134 
#define  snd_soc_dapm_dai_in 133 
#define  snd_soc_dapm_dai_link 132 
#define  snd_soc_dapm_dai_out 131 
#define  snd_soc_dapm_mux 130 
#define  snd_soc_dapm_output 129 
#define  snd_soc_dapm_switch 128 

__attribute__((used)) static int is_skl_dsp_widget_type(struct snd_soc_dapm_widget *w,
				  struct device *dev)
{
	if (w->dapm->dev != dev)
		return false;

	switch (w->id) {
	case snd_soc_dapm_dai_link:
	case snd_soc_dapm_dai_in:
	case snd_soc_dapm_aif_in:
	case snd_soc_dapm_aif_out:
	case snd_soc_dapm_dai_out:
	case snd_soc_dapm_switch:
	case snd_soc_dapm_output:
	case snd_soc_dapm_mux:

		return false;
	default:
		return true;
	}
}