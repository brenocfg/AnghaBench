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
struct snd_soc_dapm_context {scalar_t__ dev; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct rpi_cirrus_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  fll1_freq; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;
struct TYPE_2__ {scalar_t__ dev; struct snd_soc_component* component; } ;

/* Variables and functions */
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct snd_soc_pcm_runtime* get_wm5102_runtime (struct snd_soc_card*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpi_cirrus_clear_flls (struct snd_soc_card*,struct snd_soc_component*) ; 
 struct rpi_cirrus_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int rpi_cirrus_set_bias_level_post(struct snd_soc_card *card,
	struct snd_soc_dapm_context *dapm,
	enum snd_soc_bias_level level)
{
	struct rpi_cirrus_priv *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_pcm_runtime *wm5102_runtime = get_wm5102_runtime(card);
	struct snd_soc_component *wm5102_component =
		wm5102_runtime->codec_dai->component;

	if (dapm->dev != wm5102_runtime->codec_dai->dev)
		return 0;

	switch (level) {
	case SND_SOC_BIAS_STANDBY:
		mutex_lock(&priv->lock);

		dev_dbg(card->dev,
			"set_bias_post: changing FLL1 from %d to off\n",
				priv->fll1_freq);

		if (rpi_cirrus_clear_flls(card, wm5102_component))
			dev_err(card->dev,
				"set_bias_post: failed to clear FLLs\n");
		else
			priv->fll1_freq = 0;

		mutex_unlock(&priv->lock);

		break;
	default:
		break;
	}

	return 0;
}