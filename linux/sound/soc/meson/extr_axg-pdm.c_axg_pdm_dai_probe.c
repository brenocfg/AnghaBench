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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct axg_pdm {int /*<<< orphan*/  pclk; int /*<<< orphan*/  sysclk; int /*<<< orphan*/  map; TYPE_1__* cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  sys_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDM_CTRL ; 
 int /*<<< orphan*/  PDM_CTRL_BYPASS_MODE ; 
 int /*<<< orphan*/  axg_pdm_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axg_pdm_set_hcic_ctrl (struct axg_pdm*) ; 
 int /*<<< orphan*/  axg_pdm_set_hpf_ctrl (struct axg_pdm*) ; 
 int axg_pdm_set_lpf_filters (struct axg_pdm*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axg_pdm* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axg_pdm_dai_probe(struct snd_soc_dai *dai)
{
	struct axg_pdm *priv = snd_soc_dai_get_drvdata(dai);
	int ret;

	ret = clk_prepare_enable(priv->pclk);
	if (ret) {
		dev_err(dai->dev, "enabling pclk failed\n");
		return ret;
	}

	/*
	 * sysclk must be set and enabled as well to access the pdm registers
	 * Accessing the register w/o it will give a bus error.
	 */
	ret = clk_set_rate(priv->sysclk, priv->cfg->sys_rate);
	if (ret) {
		dev_err(dai->dev, "setting sysclk failed\n");
		goto err_pclk;
	}

	ret = clk_prepare_enable(priv->sysclk);
	if (ret) {
		dev_err(dai->dev, "enabling sysclk failed\n");
		goto err_pclk;
	}

	/* Make sure the device is initially disabled */
	axg_pdm_disable(priv->map);

	/* Make sure filter bypass is disabled */
	regmap_update_bits(priv->map, PDM_CTRL, PDM_CTRL_BYPASS_MODE, 0);

	/* Load filter settings */
	axg_pdm_set_hcic_ctrl(priv);
	axg_pdm_set_hpf_ctrl(priv);

	ret = axg_pdm_set_lpf_filters(priv);
	if (ret) {
		dev_err(dai->dev, "invalid filter configuration\n");
		goto err_sysclk;
	}

	return 0;

err_sysclk:
	clk_disable_unprepare(priv->sysclk);
err_pclk:
	clk_disable_unprepare(priv->pclk);
	return ret;
}