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
struct snd_soc_dai {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct cht_mc_private {int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHT_CODEC_DAI1 ; 
 int /*<<< orphan*/  CHT_CODEC_DAI2 ; 
 int EIO ; 
 int /*<<< orphan*/  RT5645_SCLK_S_RCCLK ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct snd_soc_dai* snd_soc_card_get_codec_dai (struct snd_soc_card*,int /*<<< orphan*/ ) ; 
 struct cht_mc_private* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int platform_clock_control(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *k, int  event)
{
	struct snd_soc_dapm_context *dapm = w->dapm;
	struct snd_soc_card *card = dapm->card;
	struct snd_soc_dai *codec_dai;
	struct cht_mc_private *ctx = snd_soc_card_get_drvdata(card);
	int ret;

	codec_dai = snd_soc_card_get_codec_dai(card, CHT_CODEC_DAI1);
	if (!codec_dai)
		codec_dai = snd_soc_card_get_codec_dai(card, CHT_CODEC_DAI2);

	if (!codec_dai) {
		dev_err(card->dev, "Codec dai not found; Unable to set platform clock\n");
		return -EIO;
	}

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		ret = clk_prepare_enable(ctx->mclk);
		if (ret < 0) {
			dev_err(card->dev,
				"could not configure MCLK state");
			return ret;
		}
	} else {
		/* Set codec sysclk source to its internal clock because codec PLL will
		 * be off when idle and MCLK will also be off when codec is
		 * runtime suspended. Codec needs clock for jack detection and button
		 * press. MCLK is turned off with clock framework or ACPI.
		 */
		ret = snd_soc_dai_set_sysclk(codec_dai, RT5645_SCLK_S_RCCLK,
					48000 * 512, SND_SOC_CLOCK_IN);
		if (ret < 0) {
			dev_err(card->dev, "can't set codec sysclk: %d\n", ret);
			return ret;
		}

		clk_disable_unprepare(ctx->mclk);
	}

	return 0;
}