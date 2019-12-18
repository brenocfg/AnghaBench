#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_soc_dai {int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct lochnagar_sc_priv {int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lochnagar_sc_chan_constraint ; 
 int lochnagar_sc_startup (struct snd_pcm_substream*,struct snd_soc_dai*) ; 
 int snd_pcm_hw_constraint_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct lochnagar_sc_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int lochnagar_sc_line_startup(struct snd_pcm_substream *substream,
				     struct snd_soc_dai *dai)
{
	struct snd_soc_component *comp = dai->component;
	struct lochnagar_sc_priv *priv = snd_soc_component_get_drvdata(comp);
	int ret;

	ret = clk_prepare_enable(priv->mclk);
	if (ret < 0) {
		dev_err(dai->dev, "Failed to enable MCLK: %d\n", ret);
		return ret;
	}

	ret = lochnagar_sc_startup(substream, dai);
	if (ret)
		return ret;

	return snd_pcm_hw_constraint_list(substream->runtime, 0,
					  SNDRV_PCM_HW_PARAM_CHANNELS,
					  &lochnagar_sc_chan_constraint);
}