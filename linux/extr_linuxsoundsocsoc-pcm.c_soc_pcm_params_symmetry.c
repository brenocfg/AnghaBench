#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {unsigned int num_codecs; int /*<<< orphan*/  dev; TYPE_4__** codec_dais; TYPE_2__* dai_link; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {unsigned int rate; unsigned int channels; unsigned int sample_bits; TYPE_1__* driver; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_8__ {TYPE_3__* driver; } ;
struct TYPE_7__ {unsigned int symmetric_rates; unsigned int symmetric_channels; unsigned int symmetric_samplebits; } ;
struct TYPE_6__ {scalar_t__ symmetric_samplebits; scalar_t__ symmetric_channels; scalar_t__ symmetric_rates; } ;
struct TYPE_5__ {scalar_t__ symmetric_samplebits; scalar_t__ symmetric_channels; scalar_t__ symmetric_rates; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 unsigned int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_pcm_params_symmetry(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	unsigned int rate, channels, sample_bits, symmetry, i;

	rate = params_rate(params);
	channels = params_channels(params);
	sample_bits = snd_pcm_format_physical_width(params_format(params));

	/* reject unmatched parameters when applying symmetry */
	symmetry = cpu_dai->driver->symmetric_rates ||
		rtd->dai_link->symmetric_rates;

	for (i = 0; i < rtd->num_codecs; i++)
		symmetry |= rtd->codec_dais[i]->driver->symmetric_rates;

	if (symmetry && cpu_dai->rate && cpu_dai->rate != rate) {
		dev_err(rtd->dev, "ASoC: unmatched rate symmetry: %d - %d\n",
				cpu_dai->rate, rate);
		return -EINVAL;
	}

	symmetry = cpu_dai->driver->symmetric_channels ||
		rtd->dai_link->symmetric_channels;

	for (i = 0; i < rtd->num_codecs; i++)
		symmetry |= rtd->codec_dais[i]->driver->symmetric_channels;

	if (symmetry && cpu_dai->channels && cpu_dai->channels != channels) {
		dev_err(rtd->dev, "ASoC: unmatched channel symmetry: %d - %d\n",
				cpu_dai->channels, channels);
		return -EINVAL;
	}

	symmetry = cpu_dai->driver->symmetric_samplebits ||
		rtd->dai_link->symmetric_samplebits;

	for (i = 0; i < rtd->num_codecs; i++)
		symmetry |= rtd->codec_dais[i]->driver->symmetric_samplebits;

	if (symmetry && cpu_dai->sample_bits && cpu_dai->sample_bits != sample_bits) {
		dev_err(rtd->dev, "ASoC: unmatched sample bits symmetry: %d - %d\n",
				cpu_dai->sample_bits, sample_bits);
		return -EINVAL;
	}

	return 0;
}