#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct rpi_cirrus_priv {size_t min_rate_idx; size_t max_rate_idx; } ;
struct TYPE_4__ {unsigned int value; } ;
struct TYPE_3__ {unsigned int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 TYPE_2__* max_rates ; 
 TYPE_1__* min_rates ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct rpi_cirrus_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int rpi_cirrus_startup(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_card *card = rtd->card;
	struct rpi_cirrus_priv *priv = snd_soc_card_get_drvdata(card);
	unsigned int min_rate = min_rates[priv->min_rate_idx].value;
	unsigned int max_rate = max_rates[priv->max_rate_idx].value;

	if (min_rate || max_rate) {
		if (max_rate == 0)
			max_rate = UINT_MAX;

		dev_dbg(card->dev,
			"startup: limiting rate to %u-%u\n",
			min_rate, max_rate);

		snd_pcm_hw_constraint_minmax(substream->runtime,
			SNDRV_PCM_HW_PARAM_RATE, min_rate, max_rate);
	}

	return 0;
}