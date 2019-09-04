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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct rt5677_priv {int sysclk; int* lrck; } ;

/* Variables and functions */
 size_t RT5677_AIF1 ; 
 struct rt5677_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int can_use_asrc(struct snd_soc_dapm_widget *source,
			 struct snd_soc_dapm_widget *sink)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	struct rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	if (rt5677->sysclk > rt5677->lrck[RT5677_AIF1] * 384)
		return 1;

	return 0;
}