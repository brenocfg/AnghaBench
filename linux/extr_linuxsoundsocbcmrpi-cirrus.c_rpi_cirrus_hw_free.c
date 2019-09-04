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
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; struct snd_soc_card* card; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int stream; struct snd_soc_pcm_runtime* private_data; } ;
struct rpi_cirrus_priv {unsigned int params_set; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_CLK_SRC_FLL1 ; 
 int /*<<< orphan*/  ARIZONA_CLK_SYSCLK ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct rpi_cirrus_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_component_set_sysclk (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpi_cirrus_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_card *card = rtd->card;
	struct rpi_cirrus_priv *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_component *wm5102_component = rtd->codec_dai->component;
	int ret;
	unsigned int old_params_set = priv->params_set;

	priv->params_set &= ~(1 << substream->stream);

	/* disable sysclk if this was the last open stream */
	if (priv->params_set == 0 && old_params_set) {
		dev_dbg(card->dev,
			"hw_free: Setting SYSCLK to Zero\n");

		ret = snd_soc_component_set_sysclk(wm5102_component,
			ARIZONA_CLK_SYSCLK,
			ARIZONA_CLK_SRC_FLL1,
			0,
			SND_SOC_CLOCK_IN);
		if (ret)
			dev_err(card->dev,
				"hw_free: Failed to set SYSCLK to Zero: %d\n",
				ret);
	}
	return 0;
}