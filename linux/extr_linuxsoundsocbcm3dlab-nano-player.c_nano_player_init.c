#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_stream {int formats; int rate_max; int rate_min; int /*<<< orphan*/  rates; } ;
struct snd_soc_pcm_runtime {TYPE_4__* cpu_dai; TYPE_3__* codec_dai; struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct regmap {int dummy; } ;
struct TYPE_8__ {TYPE_1__* driver; } ;
struct TYPE_7__ {TYPE_2__* driver; } ;
struct TYPE_6__ {struct snd_soc_pcm_stream playback; } ;
struct TYPE_5__ {struct snd_soc_pcm_stream playback; } ;

/* Variables and functions */
 int /*<<< orphan*/  NANO_STATUS ; 
 unsigned int NANO_STATUS_CLK ; 
 int SNDRV_PCM_FMTBIT_DSD_U32_LE ; 
 int SNDRV_PCM_FMTBIT_S32_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_KNOT ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct regmap* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_dai_set_bclk_ratio (TYPE_4__*,unsigned int) ; 

__attribute__((used)) static int nano_player_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_card *card = rtd->card;
	struct regmap *regmap = snd_soc_card_get_drvdata(card);
	struct snd_soc_pcm_stream *cpu = &rtd->cpu_dai->driver->playback;
	struct snd_soc_pcm_stream *codec = &rtd->codec_dai->driver->playback;
	unsigned int sample_bits = 32;
	unsigned int val;

	/* configure cpu dai */
	cpu->formats |= SNDRV_PCM_FMTBIT_DSD_U32_LE;
	cpu->rate_max = 768000;

	/* configure dummy codec dai */
	codec->rate_min = 44100;
	codec->rates = SNDRV_PCM_RATE_KNOT;
	codec->formats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_DSD_U32_LE;

	/* configure max supported rate */
	regmap_read(regmap, NANO_STATUS, &val);
	if (val & NANO_STATUS_CLK) {
		dev_notice(card->dev, "Board with fast clocks installed\n");
		codec->rate_max = 768000;
	} else {
		dev_notice(card->dev, "Board with normal clocks installed\n");
		codec->rate_max = 384000;
	}

	/* frame length enforced by hardware */
	return snd_soc_dai_set_bclk_ratio(rtd->cpu_dai, sample_bits * 2);
}