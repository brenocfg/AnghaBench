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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  codec_dai; struct snd_soc_card* card; } ;
struct TYPE_2__ {int idle_bias_off; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; TYPE_1__ dapm; } ;
struct byt_cht_es8316_private {int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct byt_cht_es8316_private* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_dai_set_sysclk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int byt_cht_es8316_init(struct snd_soc_pcm_runtime *runtime)
{
	struct snd_soc_card *card = runtime->card;
	struct byt_cht_es8316_private *priv = snd_soc_card_get_drvdata(card);
	int ret;

	card->dapm.idle_bias_off = true;

	/*
	 * The firmware might enable the clock at boot (this information
	 * may or may not be reflected in the enable clock register).
	 * To change the rate we must disable the clock first to cover these
	 * cases. Due to common clock framework restrictions that do not allow
	 * to disable a clock that has not been enabled, we need to enable
	 * the clock first.
	 */
	ret = clk_prepare_enable(priv->mclk);
	if (!ret)
		clk_disable_unprepare(priv->mclk);

	ret = clk_set_rate(priv->mclk, 19200000);
	if (ret)
		dev_err(card->dev, "unable to set MCLK rate\n");

	ret = clk_prepare_enable(priv->mclk);
	if (ret)
		dev_err(card->dev, "unable to enable MCLK\n");

	ret = snd_soc_dai_set_sysclk(runtime->codec_dai, 0, 19200000,
				     SND_SOC_CLOCK_IN);
	if (ret < 0) {
		dev_err(card->dev, "can't set codec clock %d\n", ret);
		return ret;
	}

	return 0;
}