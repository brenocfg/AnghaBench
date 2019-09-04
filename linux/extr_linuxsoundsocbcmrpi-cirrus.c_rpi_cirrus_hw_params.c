#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; struct snd_soc_dai* cpu_dai; struct snd_soc_card* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int stream; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct rpi_cirrus_priv {unsigned int fll1_freq; unsigned int card_rate; int params_set; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {struct snd_soc_dai* codec_dai; } ;
struct TYPE_5__ {unsigned int rate_min; unsigned int rate_max; } ;
struct TYPE_4__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_CLK_SRC_FLL1 ; 
 int /*<<< orphan*/  ARIZONA_CLK_SYSCLK ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 unsigned int calc_sysclk (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* get_wm8804_runtime (struct snd_soc_card*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 scalar_t__ rpi_cirrus_clear_flls (struct snd_soc_card*,struct snd_soc_component*) ; 
 TYPE_2__ rpi_cirrus_dai_link2_params ; 
 scalar_t__ rpi_cirrus_set_fll (struct snd_soc_card*,struct snd_soc_component*,unsigned int) ; 
 int rpi_cirrus_set_wm8804_pll (struct snd_soc_card*,struct snd_soc_dai*,unsigned int) ; 
 unsigned int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 struct rpi_cirrus_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_component_set_sysclk (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_bclk_ratio (struct snd_soc_dai*,int) ; 
 int snd_soc_dai_set_tdm_slot (TYPE_1__*,int,int,int,unsigned int) ; 

__attribute__((used)) static int rpi_cirrus_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_card *card = rtd->card;
	struct rpi_cirrus_priv *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_dai *bcm_i2s_dai = rtd->cpu_dai;
	struct snd_soc_component *wm5102_component = rtd->codec_dai->component;
	struct snd_soc_dai *wm8804_dai = get_wm8804_runtime(card)->codec_dai;

	int ret;

	unsigned int width = snd_pcm_format_physical_width(
		params_format(params));
	unsigned int rate = params_rate(params);
	unsigned int clk_freq = calc_sysclk(rate);

	mutex_lock(&priv->lock);

	dev_dbg(card->dev, "hw_params: setting rate to %d\n", rate);

	ret = snd_soc_dai_set_bclk_ratio(bcm_i2s_dai, 2 * width);
	if (ret) {
		dev_err(card->dev, "set_bclk_ratio failed: %d\n", ret);
		goto out;
	}

	ret = snd_soc_dai_set_tdm_slot(rtd->codec_dai, 0x03, 0x03, 2, width);
	if (ret) {
		dev_err(card->dev, "set_tdm_slot failed: %d\n", ret);
		goto out;
	}

	/* WM8804 supports sample rates from 32k only */
	if (rate >= 32000) {
		ret = rpi_cirrus_set_wm8804_pll(card, wm8804_dai, rate);
		if (ret)
			goto out;
	}

	ret = snd_soc_component_set_sysclk(wm5102_component,
		ARIZONA_CLK_SYSCLK,
		ARIZONA_CLK_SRC_FLL1,
		clk_freq,
		SND_SOC_CLOCK_IN);
	if (ret) {
		dev_err(card->dev, "Failed to set SYSCLK: %d\n", ret);
		goto out;
	}

	if ((priv->fll1_freq > 0) && (priv->fll1_freq != clk_freq)) {
		dev_dbg(card->dev,
			"hw_params: changing FLL1 from %d to %d\n",
			priv->fll1_freq, clk_freq);

		if (rpi_cirrus_clear_flls(card, wm5102_component)) {
			dev_err(card->dev, "hw_params: failed to clear FLLs\n");
			goto out;
		}

		if (rpi_cirrus_set_fll(card, wm5102_component, clk_freq)) {
			dev_err(card->dev, "hw_params: failed to set FLL\n");
			goto out;
		}

		priv->fll1_freq = clk_freq;
	}

	priv->card_rate = rate;
	rpi_cirrus_dai_link2_params.rate_min = rate;
	rpi_cirrus_dai_link2_params.rate_max = rate;

	priv->params_set |= 1 << substream->stream;

out:
	mutex_unlock(&priv->lock);

	return ret;
}