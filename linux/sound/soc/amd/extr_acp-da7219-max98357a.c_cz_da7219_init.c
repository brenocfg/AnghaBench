#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; struct snd_soc_dai* codec_dai; struct snd_soc_card* card; } ;
struct snd_soc_dai {int /*<<< orphan*/  name; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  jack; } ;

/* Variables and functions */
 int /*<<< orphan*/  CZ_PLAT_CLK ; 
 int /*<<< orphan*/  DA7219_CLKSRC_MCLK ; 
 int /*<<< orphan*/  DA7219_PLL_FREQ_OUT_98304 ; 
 int /*<<< orphan*/  DA7219_SYSCLK_PLL ; 
 int /*<<< orphan*/  KEY_PLAYPAUSE ; 
 int /*<<< orphan*/  KEY_VOICECOMMAND ; 
 int /*<<< orphan*/  KEY_VOLUMEDOWN ; 
 int /*<<< orphan*/  KEY_VOLUMEUP ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_BTN_1 ; 
 int SND_JACK_BTN_2 ; 
 int SND_JACK_BTN_3 ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_LINEOUT ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 void* clk_get (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ cz_jack ; 
 int /*<<< orphan*/  da7219_aad_jack_det (struct snd_soc_component*,TYPE_1__*) ; 
 void* da7219_dai_bclk ; 
 void* da7219_dai_wclk ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_jack_set_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cz_da7219_init(struct snd_soc_pcm_runtime *rtd)
{
	int ret;
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_component *component = codec_dai->component;

	dev_info(rtd->dev, "codec dai name = %s\n", codec_dai->name);

	ret = snd_soc_dai_set_sysclk(codec_dai, DA7219_CLKSRC_MCLK,
				     CZ_PLAT_CLK, SND_SOC_CLOCK_IN);
	if (ret < 0) {
		dev_err(rtd->dev, "can't set codec sysclk: %d\n", ret);
		return ret;
	}

	ret = snd_soc_dai_set_pll(codec_dai, 0, DA7219_SYSCLK_PLL,
				  CZ_PLAT_CLK, DA7219_PLL_FREQ_OUT_98304);
	if (ret < 0) {
		dev_err(rtd->dev, "can't set codec pll: %d\n", ret);
		return ret;
	}

	da7219_dai_wclk = clk_get(component->dev, "da7219-dai-wclk");
	da7219_dai_bclk = clk_get(component->dev, "da7219-dai-bclk");

	ret = snd_soc_card_jack_new(card, "Headset Jack",
				SND_JACK_HEADSET | SND_JACK_LINEOUT |
				SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				SND_JACK_BTN_2 | SND_JACK_BTN_3,
				&cz_jack, NULL, 0);
	if (ret) {
		dev_err(card->dev, "HP jack creation failed %d\n", ret);
		return ret;
	}

	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);
	snd_jack_set_key(cz_jack.jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);

	da7219_aad_jack_det(component, &cz_jack);

	return 0;
}