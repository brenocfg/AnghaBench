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
struct snd_soc_dapm_widget {struct snd_soc_dapm_context* dapm; } ;
struct snd_soc_dapm_context {struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct kbl_rt5663_private {int /*<<< orphan*/  sclk; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct kbl_rt5663_private* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int platform_clock_control(struct snd_soc_dapm_widget *w,
			struct snd_kcontrol *k, int  event)
{
	struct snd_soc_dapm_context *dapm = w->dapm;
	struct snd_soc_card *card = dapm->card;
	struct kbl_rt5663_private *priv = snd_soc_card_get_drvdata(card);
	int ret = 0;

	/*
	 * MCLK/SCLK need to be ON early for a successful synchronization of
	 * codec internal clock. And the clocks are turned off during
	 * POST_PMD after the stream is stopped.
	 */
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* Enable MCLK */
		ret = clk_set_rate(priv->mclk, 24000000);
		if (ret < 0) {
			dev_err(card->dev, "Can't set rate for mclk, err: %d\n",
				ret);
			return ret;
		}

		ret = clk_prepare_enable(priv->mclk);
		if (ret < 0) {
			dev_err(card->dev, "Can't enable mclk, err: %d\n", ret);
			return ret;
		}

		/* Enable SCLK */
		ret = clk_set_rate(priv->sclk, 3072000);
		if (ret < 0) {
			dev_err(card->dev, "Can't set rate for sclk, err: %d\n",
				ret);
			clk_disable_unprepare(priv->mclk);
			return ret;
		}

		ret = clk_prepare_enable(priv->sclk);
		if (ret < 0) {
			dev_err(card->dev, "Can't enable sclk, err: %d\n", ret);
			clk_disable_unprepare(priv->mclk);
		}
		break;
	case SND_SOC_DAPM_POST_PMD:
		clk_disable_unprepare(priv->mclk);
		clk_disable_unprepare(priv->sclk);
		break;
	default:
		return 0;
	}

	return 0;
}