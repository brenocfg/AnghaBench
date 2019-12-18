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
typedef  int u32 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct cs42xx8_priv {int* rate; int sysclk; int /*<<< orphan*/  regmap; scalar_t__ slave_mode; int /*<<< orphan*/  tx_channels; } ;
struct TYPE_3__ {int* ratio; int min_mclk; int max_mclk; int mfreq; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int CS42XX8_FM_AUTO ; 
 int CS42XX8_FM_DOUBLE ; 
 int CS42XX8_FM_QUAD ; 
 int CS42XX8_FM_SINGLE ; 
 int /*<<< orphan*/  CS42XX8_FUNCMOD ; 
 int CS42XX8_FUNCMOD_MFREQ_MASK ; 
 int CS42XX8_FUNCMOD_xC_FM (int,int) ; 
 int CS42XX8_FUNCMOD_xC_FM_MASK (int) ; 
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 TYPE_1__* cs42xx8_ratios ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 void* params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct cs42xx8_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs42xx8_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	u32 ratio[2];
	u32 rate[2];
	u32 fm[2];
	u32 i, val, mask;
	bool condition1, condition2;

	if (tx)
		cs42xx8->tx_channels = params_channels(params);

	rate[tx]  = params_rate(params);
	rate[!tx] = cs42xx8->rate[!tx];

	ratio[tx] = rate[tx] > 0 ? cs42xx8->sysclk / rate[tx] : 0;
	ratio[!tx] = rate[!tx] > 0 ? cs42xx8->sysclk / rate[!tx] : 0;

	/* Get functional mode for tx and rx according to rate */
	for (i = 0; i < 2; i++) {
		if (cs42xx8->slave_mode) {
			fm[i] = CS42XX8_FM_AUTO;
		} else {
			if (rate[i] < 50000) {
				fm[i] = CS42XX8_FM_SINGLE;
			} else if (rate[i] > 50000 && rate[i] < 100000) {
				fm[i] = CS42XX8_FM_DOUBLE;
			} else if (rate[i] > 100000 && rate[i] < 200000) {
				fm[i] = CS42XX8_FM_QUAD;
			} else {
				dev_err(component->dev,
					"unsupported sample rate\n");
				return -EINVAL;
			}
		}
	}

	for (i = 0; i < ARRAY_SIZE(cs42xx8_ratios); i++) {
		/* Is the ratio[tx] valid ? */
		condition1 = ((fm[tx] == CS42XX8_FM_AUTO) ?
			(cs42xx8_ratios[i].ratio[0] == ratio[tx] ||
			cs42xx8_ratios[i].ratio[1] == ratio[tx] ||
			cs42xx8_ratios[i].ratio[2] == ratio[tx]) :
			(cs42xx8_ratios[i].ratio[fm[tx]] == ratio[tx])) &&
			cs42xx8->sysclk >= cs42xx8_ratios[i].min_mclk &&
			cs42xx8->sysclk <= cs42xx8_ratios[i].max_mclk;

		if (!ratio[tx])
			condition1 = true;

		/* Is the ratio[!tx] valid ? */
		condition2 = ((fm[!tx] == CS42XX8_FM_AUTO) ?
			(cs42xx8_ratios[i].ratio[0] == ratio[!tx] ||
			cs42xx8_ratios[i].ratio[1] == ratio[!tx] ||
			cs42xx8_ratios[i].ratio[2] == ratio[!tx]) :
			(cs42xx8_ratios[i].ratio[fm[!tx]] == ratio[!tx]));

		if (!ratio[!tx])
			condition2 = true;

		/*
		 * Both ratio[tx] and ratio[!tx] is valid, then we get
		 * a proper MFreq.
		 */
		if (condition1 && condition2)
			break;
	}

	if (i == ARRAY_SIZE(cs42xx8_ratios)) {
		dev_err(component->dev, "unsupported sysclk ratio\n");
		return -EINVAL;
	}

	cs42xx8->rate[tx] = params_rate(params);

	mask = CS42XX8_FUNCMOD_MFREQ_MASK;
	val = cs42xx8_ratios[i].mfreq;

	regmap_update_bits(cs42xx8->regmap, CS42XX8_FUNCMOD,
			   CS42XX8_FUNCMOD_xC_FM_MASK(tx) | mask,
			   CS42XX8_FUNCMOD_xC_FM(tx, fm[tx]) | val);

	return 0;
}