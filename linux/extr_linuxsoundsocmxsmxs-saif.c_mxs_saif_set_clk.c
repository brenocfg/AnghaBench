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
typedef  int /*<<< orphan*/  u32 ;
struct mxs_saif {unsigned int cur_rate; scalar_t__ base; scalar_t__ mclk_in_use; int /*<<< orphan*/  clk; int /*<<< orphan*/  id; int /*<<< orphan*/  dev; scalar_t__ ongoing; } ;

/* Variables and functions */
 int /*<<< orphan*/  BF_SAIF_CTRL_BITCLK_MULT_RATE (int) ; 
 int /*<<< orphan*/  BM_SAIF_CTRL_BITCLK_BASE_RATE ; 
 int /*<<< orphan*/  BM_SAIF_CTRL_BITCLK_MULT_RATE ; 
 int EINVAL ; 
 scalar_t__ SAIF_CTRL ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 struct mxs_saif* mxs_saif_get_master (struct mxs_saif*) ; 

__attribute__((used)) static int mxs_saif_set_clk(struct mxs_saif *saif,
				  unsigned int mclk,
				  unsigned int rate)
{
	u32 scr;
	int ret;
	struct mxs_saif *master_saif;

	dev_dbg(saif->dev, "mclk %d rate %d\n", mclk, rate);

	/* Set master saif to generate proper clock */
	master_saif = mxs_saif_get_master(saif);
	if (!master_saif)
		return -EINVAL;

	dev_dbg(saif->dev, "master saif%d\n", master_saif->id);

	/* Checking if can playback and capture simutaneously */
	if (master_saif->ongoing && rate != master_saif->cur_rate) {
		dev_err(saif->dev,
			"can not change clock, master saif%d(rate %d) is ongoing\n",
			master_saif->id, master_saif->cur_rate);
		return -EINVAL;
	}

	scr = __raw_readl(master_saif->base + SAIF_CTRL);
	scr &= ~BM_SAIF_CTRL_BITCLK_MULT_RATE;
	scr &= ~BM_SAIF_CTRL_BITCLK_BASE_RATE;

	/*
	 * Set SAIF clock
	 *
	 * The SAIF clock should be either 384*fs or 512*fs.
	 * If MCLK is used, the SAIF clk ratio needs to match mclk ratio.
	 *  For 256x, 128x, 64x, and 32x sub-rates, set saif clk as 512*fs.
	 *  For 192x, 96x, and 48x sub-rates, set saif clk as 384*fs.
	 *
	 * If MCLK is not used, we just set saif clk to 512*fs.
	 */
	ret = clk_prepare_enable(master_saif->clk);
	if (ret)
		return ret;

	if (master_saif->mclk_in_use) {
		switch (mclk / rate) {
		case 32:
		case 64:
		case 128:
		case 256:
		case 512:
			scr &= ~BM_SAIF_CTRL_BITCLK_BASE_RATE;
			ret = clk_set_rate(master_saif->clk, 512 * rate);
			break;
		case 48:
		case 96:
		case 192:
		case 384:
			scr |= BM_SAIF_CTRL_BITCLK_BASE_RATE;
			ret = clk_set_rate(master_saif->clk, 384 * rate);
			break;
		default:
			/* SAIF MCLK should be a sub-rate of 512x or 384x */
			clk_disable_unprepare(master_saif->clk);
			return -EINVAL;
		}
	} else {
		ret = clk_set_rate(master_saif->clk, 512 * rate);
		scr &= ~BM_SAIF_CTRL_BITCLK_BASE_RATE;
	}

	clk_disable_unprepare(master_saif->clk);

	if (ret)
		return ret;

	master_saif->cur_rate = rate;

	if (!master_saif->mclk_in_use) {
		__raw_writel(scr, master_saif->base + SAIF_CTRL);
		return 0;
	}

	/*
	 * Program the over-sample rate for MCLK output
	 *
	 * The available MCLK range is 32x, 48x... 512x. The rate
	 * could be from 8kHz to 192kH.
	 */
	switch (mclk / rate) {
	case 32:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(4);
		break;
	case 64:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(3);
		break;
	case 128:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(2);
		break;
	case 256:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(1);
		break;
	case 512:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(0);
		break;
	case 48:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(3);
		break;
	case 96:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(2);
		break;
	case 192:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(1);
		break;
	case 384:
		scr |= BF_SAIF_CTRL_BITCLK_MULT_RATE(0);
		break;
	default:
		return -EINVAL;
	}

	__raw_writel(scr, master_saif->base + SAIF_CTRL);

	return 0;
}