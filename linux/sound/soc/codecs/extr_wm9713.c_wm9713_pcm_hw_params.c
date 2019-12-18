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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CENTER_LFE_MASTER ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm9713_pcm_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;

	/* enable PCM interface in master mode */
	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		snd_soc_component_update_bits(component, AC97_CENTER_LFE_MASTER,
				    0x000c, 0x0004);
		break;
	case 24:
		snd_soc_component_update_bits(component, AC97_CENTER_LFE_MASTER,
				    0x000c, 0x0008);
		break;
	case 32:
		snd_soc_component_update_bits(component, AC97_CENTER_LFE_MASTER,
				    0x000c, 0x000c);
		break;
	}
	return 0;
}