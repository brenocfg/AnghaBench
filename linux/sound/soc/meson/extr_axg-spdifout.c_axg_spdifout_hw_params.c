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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct axg_spdifout {int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int axg_spdifout_sample_fmt (struct snd_pcm_hw_params*,struct snd_soc_dai*) ; 
 int axg_spdifout_set_chsts (struct snd_pcm_hw_params*,struct snd_soc_dai*) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 struct axg_spdifout* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axg_spdifout_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *params,
				  struct snd_soc_dai *dai)
{
	struct axg_spdifout *priv = snd_soc_dai_get_drvdata(dai);
	unsigned int rate = params_rate(params);
	int ret;

	/* 2 * 32bits per subframe * 2 channels = 128 */
	ret = clk_set_rate(priv->mclk, rate * 128);
	if (ret) {
		dev_err(dai->dev, "failed to set spdif clock\n");
		return ret;
	}

	ret = axg_spdifout_sample_fmt(params, dai);
	if (ret) {
		dev_err(dai->dev, "failed to setup sample format\n");
		return ret;
	}

	ret = axg_spdifout_set_chsts(params, dai);
	if (ret) {
		dev_err(dai->dev, "failed to setup channel status words\n");
		return ret;
	}

	return 0;
}