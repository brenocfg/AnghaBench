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
struct snd_soc_pcm_runtime {size_t num; int num_codecs; struct snd_soc_dai* cpu_dai; struct snd_soc_dai** codec_dais; int /*<<< orphan*/  card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct axg_dai_link_tdm_data {int mclk_fs; } ;
struct axg_card {scalar_t__* link_data; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_OUT ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 struct axg_card* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axg_card_tdm_be_hw_params(struct snd_pcm_substream *substream,
				     struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct axg_card *priv = snd_soc_card_get_drvdata(rtd->card);
	struct axg_dai_link_tdm_data *be =
		(struct axg_dai_link_tdm_data *)priv->link_data[rtd->num];
	struct snd_soc_dai *codec_dai;
	unsigned int mclk;
	int ret, i;

	if (be->mclk_fs) {
		mclk = params_rate(params) * be->mclk_fs;

		for (i = 0; i < rtd->num_codecs; i++) {
			codec_dai = rtd->codec_dais[i];
			ret = snd_soc_dai_set_sysclk(codec_dai, 0, mclk,
						     SND_SOC_CLOCK_IN);
			if (ret && ret != -ENOTSUPP)
				return ret;
		}

		ret = snd_soc_dai_set_sysclk(rtd->cpu_dai, 0, mclk,
					     SND_SOC_CLOCK_OUT);
		if (ret && ret != -ENOTSUPP)
			return ret;
	}

	return 0;
}