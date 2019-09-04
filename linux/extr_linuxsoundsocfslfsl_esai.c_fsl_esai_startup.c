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
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {int dummy; } ;
struct fsl_esai {int /*<<< orphan*/  coreclk; int /*<<< orphan*/  spbaclk; int /*<<< orphan*/  extalclk; int /*<<< orphan*/  regmap; scalar_t__ synchronous; int /*<<< orphan*/  fsysclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESAI_SAICR_SYNC ; 
 int /*<<< orphan*/  ESAI_xCCR_xDC (int) ; 
 int /*<<< orphan*/  ESAI_xCCR_xDC_MASK ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ESAI_RCCR ; 
 int /*<<< orphan*/  REG_ESAI_SAICR ; 
 int /*<<< orphan*/  REG_ESAI_TCCR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_esai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_esai_startup(struct snd_pcm_substream *substream,
			    struct snd_soc_dai *dai)
{
	struct fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	int ret;

	/*
	 * Some platforms might use the same bit to gate all three or two of
	 * clocks, so keep all clocks open/close at the same time for safety
	 */
	ret = clk_prepare_enable(esai_priv->coreclk);
	if (ret)
		return ret;
	if (!IS_ERR(esai_priv->spbaclk)) {
		ret = clk_prepare_enable(esai_priv->spbaclk);
		if (ret)
			goto err_spbaclk;
	}
	if (!IS_ERR(esai_priv->extalclk)) {
		ret = clk_prepare_enable(esai_priv->extalclk);
		if (ret)
			goto err_extalck;
	}
	if (!IS_ERR(esai_priv->fsysclk)) {
		ret = clk_prepare_enable(esai_priv->fsysclk);
		if (ret)
			goto err_fsysclk;
	}

	if (!dai->active) {
		/* Set synchronous mode */
		regmap_update_bits(esai_priv->regmap, REG_ESAI_SAICR,
				   ESAI_SAICR_SYNC, esai_priv->synchronous ?
				   ESAI_SAICR_SYNC : 0);

		/* Set a default slot number -- 2 */
		regmap_update_bits(esai_priv->regmap, REG_ESAI_TCCR,
				   ESAI_xCCR_xDC_MASK, ESAI_xCCR_xDC(2));
		regmap_update_bits(esai_priv->regmap, REG_ESAI_RCCR,
				   ESAI_xCCR_xDC_MASK, ESAI_xCCR_xDC(2));
	}

	return 0;

err_fsysclk:
	if (!IS_ERR(esai_priv->extalclk))
		clk_disable_unprepare(esai_priv->extalclk);
err_extalck:
	if (!IS_ERR(esai_priv->spbaclk))
		clk_disable_unprepare(esai_priv->spbaclk);
err_spbaclk:
	clk_disable_unprepare(esai_priv->coreclk);

	return ret;
}