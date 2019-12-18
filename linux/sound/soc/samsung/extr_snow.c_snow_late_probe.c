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
struct snd_soc_pcm_runtime {int num_codecs; struct snd_soc_dai* codec_dai; struct snd_soc_dai** codec_dais; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_card {TYPE_1__* dai_link; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIN_PLL_RATE ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snow_late_probe(struct snd_soc_card *card)
{
	struct snd_soc_pcm_runtime *rtd;
	struct snd_soc_dai *codec_dai;

	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[0].name);

	/* In the multi-codec case codec_dais 0 is MAX98095 and 1 is HDMI. */
	if (rtd->num_codecs > 1)
		codec_dai = rtd->codec_dais[0];
	else
		codec_dai = rtd->codec_dai;

	/* Set the MCLK rate for the codec */
	return snd_soc_dai_set_sysclk(codec_dai, 0,
				FIN_PLL_RATE, SND_SOC_CLOCK_IN);
}