#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dapm_context {scalar_t__ dev; int bias_level; } ;
struct snd_soc_dai {scalar_t__ dev; } ;
struct snd_soc_card {TYPE_1__* dai_link; struct device* dev; } ;
struct codec_priv {unsigned int mclk_freq; int /*<<< orphan*/  pll_id; int /*<<< orphan*/  mclk_id; int /*<<< orphan*/  fll_id; } ;
struct fsl_asoc_card_priv {int sample_rate; int /*<<< orphan*/  sample_format; struct codec_priv codec_priv; } ;
struct device {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  SNDRV_PCM_FORMAT_S24_LE ; 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct fsl_asoc_card_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_asoc_card_set_bias_level(struct snd_soc_card *card,
					struct snd_soc_dapm_context *dapm,
					enum snd_soc_bias_level level)
{
	struct fsl_asoc_card_priv *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_pcm_runtime *rtd;
	struct snd_soc_dai *codec_dai;
	struct codec_priv *codec_priv = &priv->codec_priv;
	struct device *dev = card->dev;
	unsigned int pll_out;
	int ret;

	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[0].name);
	codec_dai = rtd->codec_dai;
	if (dapm->dev != codec_dai->dev)
		return 0;

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (dapm->bias_level != SND_SOC_BIAS_STANDBY)
			break;

		if (priv->sample_format == SNDRV_PCM_FORMAT_S24_LE)
			pll_out = priv->sample_rate * 384;
		else
			pll_out = priv->sample_rate * 256;

		ret = snd_soc_dai_set_pll(codec_dai, codec_priv->pll_id,
					  codec_priv->mclk_id,
					  codec_priv->mclk_freq, pll_out);
		if (ret) {
			dev_err(dev, "failed to start FLL: %d\n", ret);
			return ret;
		}

		ret = snd_soc_dai_set_sysclk(codec_dai, codec_priv->fll_id,
					     pll_out, SND_SOC_CLOCK_IN);
		if (ret && ret != -ENOTSUPP) {
			dev_err(dev, "failed to set SYSCLK: %d\n", ret);
			return ret;
		}
		break;

	case SND_SOC_BIAS_STANDBY:
		if (dapm->bias_level != SND_SOC_BIAS_PREPARE)
			break;

		ret = snd_soc_dai_set_sysclk(codec_dai, codec_priv->mclk_id,
					     codec_priv->mclk_freq,
					     SND_SOC_CLOCK_IN);
		if (ret && ret != -ENOTSUPP) {
			dev_err(dev, "failed to switch away from FLL: %d\n", ret);
			return ret;
		}

		ret = snd_soc_dai_set_pll(codec_dai, codec_priv->pll_id, 0, 0, 0);
		if (ret) {
			dev_err(dev, "failed to stop FLL: %d\n", ret);
			return ret;
		}
		break;

	default:
		break;
	}

	return 0;
}