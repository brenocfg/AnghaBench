#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_widget {TYPE_1__* dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct rpi_cirrus_priv {int card_rate; unsigned int fll1_freq; int sync_path_enable; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {TYPE_2__* codec_dai; } ;
struct TYPE_5__ {struct snd_soc_component* component; } ;
struct TYPE_4__ {struct snd_soc_card* card; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 unsigned int calc_sysclk (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* get_wm5102_runtime (struct snd_soc_card*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpi_cirrus_clear_flls (struct snd_soc_card*,struct snd_soc_component*) ; 
 int rpi_cirrus_set_fll_refclk (struct snd_soc_card*,struct snd_soc_component*,unsigned int,unsigned int) ; 
 struct rpi_cirrus_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int rpi_cirrus_spdif_rx_enable_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_card *card = w->dapm->card;
	struct rpi_cirrus_priv *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_component *wm5102_component =
		get_wm5102_runtime(card)->codec_dai->component;

	unsigned int clk_freq, aif2_freq;
	int ret = 0;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		mutex_lock(&priv->lock);

		/* Enable sync path in case of SPDIF capture use case */

		clk_freq = calc_sysclk(priv->card_rate);
		aif2_freq = 64 * priv->card_rate;

		dev_dbg(card->dev,
			"spdif_rx: changing FLL1 to use Ref Clock clk: %d spdif: %d\n",
			clk_freq, aif2_freq);

		ret = rpi_cirrus_clear_flls(card, wm5102_component);
		if (ret) {
			dev_err(card->dev, "spdif_rx: failed to clear FLLs\n");
			goto out;
		}

		ret = rpi_cirrus_set_fll_refclk(card, wm5102_component,
			clk_freq, aif2_freq);

		if (ret) {
			dev_err(card->dev, "spdif_rx: failed to set FLLs\n");
			goto out;
		}

		/* set to negative to indicate we're doing spdif rx */
		priv->fll1_freq = -clk_freq;
		priv->sync_path_enable = 1;
		break;

	case SND_SOC_DAPM_POST_PMD:
		mutex_lock(&priv->lock);
		priv->sync_path_enable = 0;
		break;

	default:
		return 0;
	}

out:
	mutex_unlock(&priv->lock);
	return ret;
}