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
typedef  scalar_t__ u8 ;
struct omap_mcbsp {int /*<<< orphan*/  dev; int /*<<< orphan*/  fclk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 scalar_t__ MCBSP_CLKS_PAD_SRC ; 
 scalar_t__ MCBSP_CLKS_PRCM_SRC ; 
 struct clk* clk_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int clk_set_parent (int /*<<< orphan*/ ,struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2_mcbsp_set_clks_src(struct omap_mcbsp *mcbsp, u8 fck_src_id)
{
	struct clk *fck_src;
	const char *src;
	int r;

	if (fck_src_id == MCBSP_CLKS_PAD_SRC)
		src = "pad_fck";
	else if (fck_src_id == MCBSP_CLKS_PRCM_SRC)
		src = "prcm_fck";
	else
		return -EINVAL;

	fck_src = clk_get(mcbsp->dev, src);
	if (IS_ERR(fck_src)) {
		dev_err(mcbsp->dev, "CLKS: could not clk_get() %s\n", src);
		return -EINVAL;
	}

	pm_runtime_put_sync(mcbsp->dev);

	r = clk_set_parent(mcbsp->fclk, fck_src);
	if (r) {
		dev_err(mcbsp->dev, "CLKS: could not clk_set_parent() to %s\n",
			src);
		clk_put(fck_src);
		return r;
	}

	pm_runtime_get_sync(mcbsp->dev);

	clk_put(fck_src);

	return 0;
}