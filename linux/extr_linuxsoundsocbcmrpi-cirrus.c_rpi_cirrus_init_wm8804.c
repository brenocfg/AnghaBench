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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct rpi_cirrus_priv {unsigned int* iec958_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPI_CIRRUS_DEFAULT_RATE ; 
 int /*<<< orphan*/  WM8804_CLKOUT_HZ ; 
 int /*<<< orphan*/  WM8804_CLKOUT_SRC_OSCCLK ; 
 int /*<<< orphan*/  WM8804_MCLKDIV_256FS ; 
 int /*<<< orphan*/  WM8804_MCLK_DIV ; 
 scalar_t__ WM8804_SPDTX1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int rpi_cirrus_set_wm8804_pll (struct snd_soc_card*,struct snd_soc_dai*,int /*<<< orphan*/ ) ; 
 struct rpi_cirrus_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_component_read (struct snd_soc_component*,scalar_t__,unsigned int*) ; 
 int snd_soc_dai_set_clkdiv (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpi_cirrus_init_wm8804(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_component *component = codec_dai->component;
	struct snd_soc_card *card = rtd->card;
	struct rpi_cirrus_priv *priv = snd_soc_card_get_drvdata(card);
	unsigned int val, mask;
	int i, ret;

	for (i = 0; i < 4; i++) {
		ret = snd_soc_component_read(component,
			WM8804_SPDTX1 + i, &val);
		if (ret)
			return ret;
		mask = (i == 3) ? 0x3f : 0xff;
		priv->iec958_status[i] = val & mask;
	}

	/* Setup for 256fs */
	ret = snd_soc_dai_set_clkdiv(codec_dai,
		WM8804_MCLK_DIV, WM8804_MCLKDIV_256FS);
	if (ret) {
		dev_err(card->dev,
			"init_wm8804: Failed to set MCLK_DIV to 256fs: %d\n",
			ret);
		return ret;
	}

	/* Output OSC on CLKOUT */
	ret = snd_soc_dai_set_sysclk(codec_dai,
		WM8804_CLKOUT_SRC_OSCCLK, WM8804_CLKOUT_HZ, 0);
	if (ret)
		dev_err(card->dev,
			"init_wm8804: Failed to set CLKOUT as OSC Frequency: %d\n",
			ret);

	/* Init PLL with default samplerate */
	ret = rpi_cirrus_set_wm8804_pll(card, codec_dai,
		RPI_CIRRUS_DEFAULT_RATE);
	if (ret)
		dev_err(card->dev,
			"init_wm8804: Failed to setup PLL for %dHz: %d\n",
			RPI_CIRRUS_DEFAULT_RATE, ret);

	return ret;
}