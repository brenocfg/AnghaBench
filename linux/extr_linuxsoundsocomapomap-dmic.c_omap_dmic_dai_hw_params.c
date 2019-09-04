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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_dmaengine_dai_dma_data {int maxburst; } ;
struct omap_dmic {scalar_t__ clk_div; int threshold; int latency; int /*<<< orphan*/  dev; scalar_t__ ch_enabled; int /*<<< orphan*/  fclk_freq; int /*<<< orphan*/  out_freq; } ;

/* Variables and functions */
 int EINVAL ; 
 int OMAP_DMIC_THRES_MAX ; 
 scalar_t__ OMAP_DMIC_UP1_ENABLE ; 
 scalar_t__ OMAP_DMIC_UP2_ENABLE ; 
 scalar_t__ OMAP_DMIC_UP3_ENABLE ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ omap_dmic_select_divider (struct omap_dmic*,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 struct snd_dmaengine_dai_dma_data* snd_soc_dai_get_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*) ; 
 struct omap_dmic* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int omap_dmic_dai_hw_params(struct snd_pcm_substream *substream,
				    struct snd_pcm_hw_params *params,
				    struct snd_soc_dai *dai)
{
	struct omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);
	struct snd_dmaengine_dai_dma_data *dma_data;
	int channels;

	dmic->clk_div = omap_dmic_select_divider(dmic, params_rate(params));
	if (dmic->clk_div < 0) {
		dev_err(dmic->dev, "no valid divider for %dHz from %dHz\n",
			dmic->out_freq, dmic->fclk_freq);
		return -EINVAL;
	}

	dmic->ch_enabled = 0;
	channels = params_channels(params);
	switch (channels) {
	case 6:
		dmic->ch_enabled |= OMAP_DMIC_UP3_ENABLE;
		/* fall through */
	case 4:
		dmic->ch_enabled |= OMAP_DMIC_UP2_ENABLE;
		/* fall through */
	case 2:
		dmic->ch_enabled |= OMAP_DMIC_UP1_ENABLE;
		break;
	default:
		dev_err(dmic->dev, "invalid number of legacy channels\n");
		return -EINVAL;
	}

	/* packet size is threshold * channels */
	dma_data = snd_soc_dai_get_dma_data(dai, substream);
	dma_data->maxburst = dmic->threshold * channels;
	dmic->latency = (OMAP_DMIC_THRES_MAX - dmic->threshold) * USEC_PER_SEC /
			params_rate(params);

	return 0;
}