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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct cs42xx8_priv {int /*<<< orphan*/  regmap; scalar_t__* rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS42XX8_FM_AUTO ; 
 int /*<<< orphan*/  CS42XX8_FUNCMOD ; 
 int /*<<< orphan*/  CS42XX8_FUNCMOD_xC_FM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS42XX8_FUNCMOD_xC_FM_MASK (int) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs42xx8_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs42xx8_hw_free(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

	/* Clear stored rate */
	cs42xx8->rate[tx] = 0;

	regmap_update_bits(cs42xx8->regmap, CS42XX8_FUNCMOD,
			   CS42XX8_FUNCMOD_xC_FM_MASK(tx),
			   CS42XX8_FUNCMOD_xC_FM(tx, CS42XX8_FM_AUTO));
	return 0;
}