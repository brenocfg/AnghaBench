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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; TYPE_1__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct pcm512x_priv {int /*<<< orphan*/  sclk; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_48EN_RATE ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCM512x_GPIO_CONTROL_1 ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_allo_boss_gpio_mute (struct snd_soc_card*) ; 
 scalar_t__ snd_soc_allo_boss_master ; 
 struct pcm512x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int snd_allo_boss_startup(
	struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = rtd->codec_dai->component;
	struct snd_soc_card *card = rtd->card;

	snd_soc_component_update_bits(component, PCM512x_GPIO_CONTROL_1, 0x08, 0x08);
	snd_allo_boss_gpio_mute(card);

	if (snd_soc_allo_boss_master) {
		struct pcm512x_priv *priv = snd_soc_component_get_drvdata(component);
		/*
		 * Default sclk to CLK_48EN_RATE, otherwise codec
		 * pcm512x_dai_startup_master method could call
		 * snd_pcm_hw_constraint_ratnums using CLK_44EN/64
		 * which will mask 384k sample rate.
		 */
		if (!IS_ERR(priv->sclk))
			clk_set_rate(priv->sclk, CLK_48EN_RATE);
	}

	return 0;
}