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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct ad193x_priv {unsigned int sysclk; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ad193x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ad193x_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct ad193x_priv *ad193x = snd_soc_component_get_drvdata(component);
	switch (freq) {
	case 12288000:
	case 18432000:
	case 24576000:
	case 36864000:
		ad193x->sysclk = freq;
		return 0;
	}
	return -EINVAL;
}