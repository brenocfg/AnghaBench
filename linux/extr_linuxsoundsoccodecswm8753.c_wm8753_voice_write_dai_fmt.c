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
struct wm8753_priv {scalar_t__ dai_func; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 struct wm8753_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int wm8753_mode1v_set_dai_fmt (struct snd_soc_component*,unsigned int) ; 
 int wm8753_pcm_set_dai_fmt (struct snd_soc_component*,unsigned int) ; 

__attribute__((used)) static int wm8753_voice_write_dai_fmt(struct snd_soc_component *component,
		unsigned int fmt)
{
	struct wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);
	int ret = 0;

	if (wm8753->dai_func != 0)
		return 0;

	ret = wm8753_mode1v_set_dai_fmt(component, fmt);
	if (ret)
		return ret;
	ret = wm8753_pcm_set_dai_fmt(component, fmt);
	if (ret)
		return ret;

	return 0;
}