#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_2__* dai_link; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; scalar_t__ sample_bits; TYPE_1__* driver; scalar_t__ channels; scalar_t__ rate; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_4__ {scalar_t__ symmetric_samplebits; scalar_t__ symmetric_channels; scalar_t__ symmetric_rates; } ;
struct TYPE_3__ {scalar_t__ symmetric_samplebits; scalar_t__ symmetric_channels; scalar_t__ symmetric_rates; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_pcm_hw_constraint_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int soc_pcm_apply_symmetry(struct snd_pcm_substream *substream,
					struct snd_soc_dai *soc_dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int ret;

	if (soc_dai->rate && (soc_dai->driver->symmetric_rates ||
				rtd->dai_link->symmetric_rates)) {
		dev_dbg(soc_dai->dev, "ASoC: Symmetry forces %dHz rate\n",
				soc_dai->rate);

		ret = snd_pcm_hw_constraint_single(substream->runtime,
						SNDRV_PCM_HW_PARAM_RATE,
						soc_dai->rate);
		if (ret < 0) {
			dev_err(soc_dai->dev,
				"ASoC: Unable to apply rate constraint: %d\n",
				ret);
			return ret;
		}
	}

	if (soc_dai->channels && (soc_dai->driver->symmetric_channels ||
				rtd->dai_link->symmetric_channels)) {
		dev_dbg(soc_dai->dev, "ASoC: Symmetry forces %d channel(s)\n",
				soc_dai->channels);

		ret = snd_pcm_hw_constraint_single(substream->runtime,
						SNDRV_PCM_HW_PARAM_CHANNELS,
						soc_dai->channels);
		if (ret < 0) {
			dev_err(soc_dai->dev,
				"ASoC: Unable to apply channel symmetry constraint: %d\n",
				ret);
			return ret;
		}
	}

	if (soc_dai->sample_bits && (soc_dai->driver->symmetric_samplebits ||
				rtd->dai_link->symmetric_samplebits)) {
		dev_dbg(soc_dai->dev, "ASoC: Symmetry forces %d sample bits\n",
				soc_dai->sample_bits);

		ret = snd_pcm_hw_constraint_single(substream->runtime,
						SNDRV_PCM_HW_PARAM_SAMPLE_BITS,
						soc_dai->sample_bits);
		if (ret < 0) {
			dev_err(soc_dai->dev,
				"ASoC: Unable to apply sample bits symmetry constraint: %d\n",
				ret);
			return ret;
		}
	}

	return 0;
}