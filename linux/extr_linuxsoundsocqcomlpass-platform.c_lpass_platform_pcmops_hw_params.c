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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int stream; struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_runtime {struct lpass_pcm_data* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct lpass_variant {int dmactl_audif_start; } ;
struct lpass_pcm_data {int i2s_port; int dma_ch; } ;
struct lpass_data {int /*<<< orphan*/  lpaif_map; struct lpass_variant* variant; } ;
typedef  int /*<<< orphan*/  snd_pcm_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 unsigned int LPAIF_DMACTL_AUDINTF (int) ; 
 unsigned int LPAIF_DMACTL_BURSTEN_INCR4 ; 
 unsigned int LPAIF_DMACTL_FIFOWM_8 ; 
 int /*<<< orphan*/  LPAIF_DMACTL_REG (struct lpass_variant*,int,int) ; 
 unsigned int LPAIF_DMACTL_WPSCNT_EIGHT ; 
 unsigned int LPAIF_DMACTL_WPSCNT_FOUR ; 
 unsigned int LPAIF_DMACTL_WPSCNT_ONE ; 
 unsigned int LPAIF_DMACTL_WPSCNT_SIX ; 
 unsigned int LPAIF_DMACTL_WPSCNT_THREE ; 
 unsigned int LPAIF_DMACTL_WPSCNT_TWO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 struct lpass_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpass_platform_pcmops_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *soc_runtime = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(soc_runtime, DRV_NAME);
	struct lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	struct snd_pcm_runtime *rt = substream->runtime;
	struct lpass_pcm_data *pcm_data = rt->private_data;
	struct lpass_variant *v = drvdata->variant;
	snd_pcm_format_t format = params_format(params);
	unsigned int channels = params_channels(params);
	unsigned int regval;
	int ch, dir = substream->stream;
	int bitwidth;
	int ret, dma_port = pcm_data->i2s_port + v->dmactl_audif_start;

	ch = pcm_data->dma_ch;

	bitwidth = snd_pcm_format_width(format);
	if (bitwidth < 0) {
		dev_err(soc_runtime->dev, "invalid bit width given: %d\n",
				bitwidth);
		return bitwidth;
	}

	regval = LPAIF_DMACTL_BURSTEN_INCR4 |
			LPAIF_DMACTL_AUDINTF(dma_port) |
			LPAIF_DMACTL_FIFOWM_8;

	switch (bitwidth) {
	case 16:
		switch (channels) {
		case 1:
		case 2:
			regval |= LPAIF_DMACTL_WPSCNT_ONE;
			break;
		case 4:
			regval |= LPAIF_DMACTL_WPSCNT_TWO;
			break;
		case 6:
			regval |= LPAIF_DMACTL_WPSCNT_THREE;
			break;
		case 8:
			regval |= LPAIF_DMACTL_WPSCNT_FOUR;
			break;
		default:
			dev_err(soc_runtime->dev,
				"invalid PCM config given: bw=%d, ch=%u\n",
				bitwidth, channels);
			return -EINVAL;
		}
		break;
	case 24:
	case 32:
		switch (channels) {
		case 1:
			regval |= LPAIF_DMACTL_WPSCNT_ONE;
			break;
		case 2:
			regval |= LPAIF_DMACTL_WPSCNT_TWO;
			break;
		case 4:
			regval |= LPAIF_DMACTL_WPSCNT_FOUR;
			break;
		case 6:
			regval |= LPAIF_DMACTL_WPSCNT_SIX;
			break;
		case 8:
			regval |= LPAIF_DMACTL_WPSCNT_EIGHT;
			break;
		default:
			dev_err(soc_runtime->dev,
				"invalid PCM config given: bw=%d, ch=%u\n",
				bitwidth, channels);
			return -EINVAL;
		}
		break;
	default:
		dev_err(soc_runtime->dev, "invalid PCM config given: bw=%d, ch=%u\n",
			bitwidth, channels);
		return -EINVAL;
	}

	ret = regmap_write(drvdata->lpaif_map,
			LPAIF_DMACTL_REG(v, ch, dir), regval);
	if (ret) {
		dev_err(soc_runtime->dev, "error writing to rdmactl reg: %d\n",
			ret);
		return ret;
	}

	return 0;
}