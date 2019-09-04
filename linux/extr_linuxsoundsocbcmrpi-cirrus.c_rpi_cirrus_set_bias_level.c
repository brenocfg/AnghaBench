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
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; } ;
struct snd_soc_dapm_context {scalar_t__ dev; int /*<<< orphan*/  bias_level; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct rpi_cirrus_priv {unsigned int fll1_freq; int /*<<< orphan*/  lock; int /*<<< orphan*/  card_rate; int /*<<< orphan*/  sync_path_enable; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;
struct TYPE_2__ {scalar_t__ dev; struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_ON ; 
#define  SND_SOC_BIAS_PREPARE 128 
 unsigned int calc_sysclk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct snd_soc_pcm_runtime* get_wm5102_runtime (struct snd_soc_card*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpi_cirrus_set_fll (struct snd_soc_card*,struct snd_soc_component*,unsigned int) ; 
 struct rpi_cirrus_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int rpi_cirrus_set_bias_level(struct snd_soc_card *card,
	struct snd_soc_dapm_context *dapm,
	enum snd_soc_bias_level level)
{
	struct rpi_cirrus_priv *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_pcm_runtime *wm5102_runtime = get_wm5102_runtime(card);
	struct snd_soc_component *wm5102_component =
		wm5102_runtime->codec_dai->component;

	int ret = 0;
	unsigned int clk_freq;

	if (dapm->dev != wm5102_runtime->codec_dai->dev)
		return 0;

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (dapm->bias_level == SND_SOC_BIAS_ON)
			break;

		mutex_lock(&priv->lock);

		if (!priv->sync_path_enable) {
			clk_freq = calc_sysclk(priv->card_rate);

			dev_dbg(card->dev,
				"set_bias: changing FLL1 from %d to %d\n",
				priv->fll1_freq, clk_freq);

			ret = rpi_cirrus_set_fll(card,
				wm5102_component, clk_freq);
			if (ret)
				dev_err(card->dev,
					"set_bias: Failed to set FLL1\n");
			else
				priv->fll1_freq = clk_freq;
		}
		mutex_unlock(&priv->lock);
		break;
	default:
		break;
	}

	return ret;
}