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
struct cs4271_private {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4271_VOLA ; 
 int CS4271_VOLA_MUTE ; 
 int /*<<< orphan*/  CS4271_VOLB ; 
 int CS4271_VOLB_MUTE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct cs4271_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs4271_mute_stream(struct snd_soc_dai *dai, int mute, int stream)
{
	struct snd_soc_component *component = dai->component;
	struct cs4271_private *cs4271 = snd_soc_component_get_drvdata(component);
	int ret;
	int val_a = 0;
	int val_b = 0;

	if (stream != SNDRV_PCM_STREAM_PLAYBACK)
		return 0;

	if (mute) {
		val_a = CS4271_VOLA_MUTE;
		val_b = CS4271_VOLB_MUTE;
	}

	ret = regmap_update_bits(cs4271->regmap, CS4271_VOLA,
				 CS4271_VOLA_MUTE, val_a);
	if (ret < 0)
		return ret;

	ret = regmap_update_bits(cs4271->regmap, CS4271_VOLB,
				 CS4271_VOLB_MUTE, val_b);
	if (ret < 0)
		return ret;

	return 0;
}