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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; struct snd_soc_dai_link* dai_link; TYPE_1__* codec_dai; } ;
struct snd_soc_dai_link {char* name; char* stream_name; int dai_fmt; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct pcm512x_priv {int /*<<< orphan*/  sclk; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_48EN_RATE ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCM512x_BCLK_LRCLK_CFG ; 
 int /*<<< orphan*/  PCM512x_GPIO_CONTROL_1 ; 
 int /*<<< orphan*/  PCM512x_GPIO_EN ; 
 int /*<<< orphan*/  PCM512x_GPIO_OUTPUT_4 ; 
 int /*<<< orphan*/  PCM512x_MASTER_CLKDIV_2 ; 
 int /*<<< orphan*/  PCM512x_MASTER_MODE ; 
 int SND_SOC_DAIFMT_CBM_CFM ; 
 int SND_SOC_DAIFMT_I2S ; 
 int SND_SOC_DAIFMT_NB_NF ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ digital_gain_0db_limit ; 
 scalar_t__ slave ; 
 int snd_allo_boss_is_master_card (struct snd_soc_component*) ; 
 int snd_soc_allo_boss_master ; 
 struct pcm512x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int snd_soc_limit_volume (struct snd_soc_card*,char*,int) ; 

__attribute__((used)) static int snd_allo_boss_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = rtd->codec_dai->component;
	struct pcm512x_priv *priv = snd_soc_component_get_drvdata(component);

	if (slave)
		snd_soc_allo_boss_master = false;
	else
		snd_soc_allo_boss_master =
			snd_allo_boss_is_master_card(component);

	if (snd_soc_allo_boss_master) {
		struct snd_soc_dai_link *dai = rtd->dai_link;

		dai->name = "BossDAC";
		dai->stream_name = "Boss DAC HiFi [Master]";
		dai->dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
			| SND_SOC_DAIFMT_CBM_CFM;

		snd_soc_component_update_bits(component, PCM512x_BCLK_LRCLK_CFG, 0x31, 0x11);
		snd_soc_component_update_bits(component, PCM512x_MASTER_MODE, 0x03, 0x03);
		snd_soc_component_update_bits(component, PCM512x_MASTER_CLKDIV_2, 0x7f, 63);
		/*
		* Default sclk to CLK_48EN_RATE, otherwise codec
		*  pcm512x_dai_startup_master method could call
		*  snd_pcm_hw_constraint_ratnums using CLK_44EN/64
		*  which will mask 384k sample rate.
		*/
		if (!IS_ERR(priv->sclk))
			clk_set_rate(priv->sclk, CLK_48EN_RATE);
	} else {
		priv->sclk = ERR_PTR(-ENOENT);
	}

	snd_soc_component_update_bits(component, PCM512x_GPIO_EN, 0x08, 0x08);
	snd_soc_component_update_bits(component, PCM512x_GPIO_OUTPUT_4, 0x0f, 0x02);
	snd_soc_component_update_bits(component, PCM512x_GPIO_CONTROL_1, 0x08, 0x08);

	if (digital_gain_0db_limit) {
		int ret;
		struct snd_soc_card *card = rtd->card;

		ret = snd_soc_limit_volume(card, "Digital Playback Volume",
				207);
		if (ret < 0)
			dev_warn(card->dev, "Failed to set volume limit: %d\n",
					ret);
	}

	return 0;
}