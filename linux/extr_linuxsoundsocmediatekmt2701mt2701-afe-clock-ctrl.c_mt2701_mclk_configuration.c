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
struct mtk_base_afe {int /*<<< orphan*/  dev; struct mt2701_afe_private* platform_priv; } ;
struct mt2701_i2s_path {int mclk_rate; int /*<<< orphan*/  div_ck; int /*<<< orphan*/  sel_ck; } ;
struct mt2701_afe_private {int /*<<< orphan*/ * base_ck; struct mt2701_i2s_path* i2s_path; } ;

/* Variables and functions */
 int EINVAL ; 
 int MT2701_PLL_DOMAIN_0_RATE ; 
 int MT2701_PLL_DOMAIN_1_RATE ; 
 size_t MT2701_TOP_AUD_MCLK_SRC0 ; 
 size_t MT2701_TOP_AUD_MCLK_SRC1 ; 
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 

int mt2701_mclk_configuration(struct mtk_base_afe *afe, int id)

{
	struct mt2701_afe_private *priv = afe->platform_priv;
	struct mt2701_i2s_path *i2s_path = &priv->i2s_path[id];
	int ret = -EINVAL;

	/* Set mclk source */
	if (!(MT2701_PLL_DOMAIN_0_RATE % i2s_path->mclk_rate))
		ret = clk_set_parent(i2s_path->sel_ck,
				     priv->base_ck[MT2701_TOP_AUD_MCLK_SRC0]);
	else if (!(MT2701_PLL_DOMAIN_1_RATE % i2s_path->mclk_rate))
		ret = clk_set_parent(i2s_path->sel_ck,
				     priv->base_ck[MT2701_TOP_AUD_MCLK_SRC1]);

	if (ret) {
		dev_err(afe->dev, "failed to set mclk source\n");
		return ret;
	}

	/* Set mclk divider */
	ret = clk_set_rate(i2s_path->div_ck, i2s_path->mclk_rate);
	if (ret) {
		dev_err(afe->dev, "failed to set mclk divider %d\n", ret);
		return ret;
	}

	return 0;
}