#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct cs42xx8_priv {size_t sysclk; int /*<<< orphan*/  regmap; scalar_t__ slave_mode; int /*<<< orphan*/  tx_channels; } ;
struct TYPE_3__ {size_t ratio; size_t mclk; size_t speed; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 size_t CS42XX8_FM_AUTO ; 
 int /*<<< orphan*/  CS42XX8_FUNCMOD ; 
 size_t CS42XX8_FUNCMOD_MFREQ_MASK ; 
 size_t CS42XX8_FUNCMOD_xC_FM (int,size_t) ; 
 size_t CS42XX8_FUNCMOD_xC_FM_MASK (int) ; 
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 TYPE_1__* cs42xx8_ratios ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 size_t params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t) ; 
 struct cs42xx8_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs42xx8_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	u32 ratio = cs42xx8->sysclk / params_rate(params);
	u32 i, fm, val, mask;

	if (tx)
		cs42xx8->tx_channels = params_channels(params);

	for (i = 0; i < ARRAY_SIZE(cs42xx8_ratios); i++) {
		if (cs42xx8_ratios[i].ratio == ratio)
			break;
	}

	if (i == ARRAY_SIZE(cs42xx8_ratios)) {
		dev_err(component->dev, "unsupported sysclk ratio\n");
		return -EINVAL;
	}

	mask = CS42XX8_FUNCMOD_MFREQ_MASK;
	val = cs42xx8_ratios[i].mclk;

	fm = cs42xx8->slave_mode ? CS42XX8_FM_AUTO : cs42xx8_ratios[i].speed;

	regmap_update_bits(cs42xx8->regmap, CS42XX8_FUNCMOD,
			   CS42XX8_FUNCMOD_xC_FM_MASK(tx) | mask,
			   CS42XX8_FUNCMOD_xC_FM(tx, fm) | val);

	return 0;
}