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
struct sgtl5000_priv {unsigned int sysclk; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SGTL5000_SYSCLK 128 
 struct sgtl5000_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int sgtl5000_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				   int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct sgtl5000_priv *sgtl5000 = snd_soc_component_get_drvdata(component);

	switch (clk_id) {
	case SGTL5000_SYSCLK:
		sgtl5000->sysclk = freq;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}