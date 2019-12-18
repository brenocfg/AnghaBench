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
struct snd_soc_dapm_context {int bias_level; scalar_t__ component; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int snd_soc_component_set_bias_level (scalar_t__,int) ; 

int snd_soc_dapm_force_bias_level(struct snd_soc_dapm_context *dapm,
	enum snd_soc_bias_level level)
{
	int ret = 0;

	if (dapm->component)
		ret = snd_soc_component_set_bias_level(dapm->component, level);

	if (ret == 0)
		dapm->bias_level = level;

	return ret;
}