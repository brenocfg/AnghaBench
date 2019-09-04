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
struct pcm512x_priv {int lrclk_div; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pcm512x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int pcm512x_set_tdm_slot(struct snd_soc_dai *dai,
	unsigned int tx_mask, unsigned int rx_mask,
	int slots, int width)
{
	struct snd_soc_component *component = dai->component;
	struct pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);

	switch (slots) {
	case 0:
		pcm512x->lrclk_div = 0;
		return 0;
	case 2:
		if (tx_mask != 0x03 || rx_mask != 0x03)
			return -EINVAL;
		pcm512x->lrclk_div = slots * width;
		return 0;
	default:
		return -EINVAL;
	}
}