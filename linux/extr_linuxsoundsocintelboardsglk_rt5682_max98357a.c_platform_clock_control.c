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

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GLK_PLAT_CLK_FREQ ; 
 int /*<<< orphan*/  GLK_REALTEK_CODEC_DAI ; 
 int /*<<< orphan*/  RT5682_PLL1_S_MCLK ; 
 int /*<<< orphan*/  RT5682_PLL_FREQ ; 
 scalar_t__ SND_SOC_DAPM_EVENT_OFF (int) ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct snd_soc_dai* snd_soc_card_get_codec_dai (struct snd_soc_card*,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int platform_clock_control(struct snd_soc_dapm_widget *w,
					struct snd_kcontrol *k, int  event)
{
	struct snd_soc_dapm_context *dapm = w->dapm;
	struct snd_soc_card *card = dapm->card;
	struct snd_soc_dai *codec_dai;
	int ret = 0;

	codec_dai = snd_soc_card_get_codec_dai(card, GLK_REALTEK_CODEC_DAI);
	if (!codec_dai) {
		dev_err(card->dev, "Codec dai not found; Unable to set/unset codec pll\n");
		return -EIO;
	}

	if (SND_SOC_DAPM_EVENT_OFF(event)) {
		ret = snd_soc_dai_set_sysclk(codec_dai, 0, 0, 0);
		if (ret)
			dev_err(card->dev, "failed to stop sysclk: %d\n", ret);
	} else if (SND_SOC_DAPM_EVENT_ON(event)) {
		ret = snd_soc_dai_set_pll(codec_dai, 0, RT5682_PLL1_S_MCLK,
					GLK_PLAT_CLK_FREQ, RT5682_PLL_FREQ);
		if (ret < 0) {
			dev_err(card->dev, "can't set codec pll: %d\n", ret);
			return ret;
		}
	}

	if (ret)
		dev_err(card->dev, "failed to start internal clk: %d\n", ret);

	return ret;
}