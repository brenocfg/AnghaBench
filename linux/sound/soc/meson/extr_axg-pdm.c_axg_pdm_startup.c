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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct axg_pdm {int /*<<< orphan*/  map; int /*<<< orphan*/  dclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  axg_pdm_filters_enable (int /*<<< orphan*/ ,int) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct axg_pdm* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axg_pdm_startup(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct axg_pdm *priv = snd_soc_dai_get_drvdata(dai);
	int ret;

	ret = clk_prepare_enable(priv->dclk);
	if (ret) {
		dev_err(dai->dev, "enabling dclk failed\n");
		return ret;
	}

	/* Enable the filters */
	axg_pdm_filters_enable(priv->map, true);

	return ret;
}