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

/* Variables and functions */
 int M98090_DVM_MASK ; 
 int /*<<< orphan*/  M98090_REG_DAI_PLAYBACK_LEVEL ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int max98090_dai_digital_mute(struct snd_soc_dai *codec_dai, int mute)
{
	struct snd_soc_component *component = codec_dai->component;
	int regval;

	regval = mute ? M98090_DVM_MASK : 0;
	snd_soc_component_update_bits(component, M98090_REG_DAI_PLAYBACK_LEVEL,
		M98090_DVM_MASK, regval);

	return 0;
}