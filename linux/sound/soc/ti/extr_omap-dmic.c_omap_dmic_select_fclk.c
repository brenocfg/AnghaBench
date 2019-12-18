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
struct omap_dmic {unsigned int fclk_freq; int sysclk; int /*<<< orphan*/  dev; int /*<<< orphan*/  mutex; scalar_t__ active; int /*<<< orphan*/  fclk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct clk*) ; 
#define  OMAP_DMIC_SYSCLK_PAD_CLKS 130 
#define  OMAP_DMIC_SYSCLK_SLIMBLUS_CLKS 129 
#define  OMAP_DMIC_SYSCLK_SYNC_MUX_CLKS 128 
 struct clk* clk_get (int /*<<< orphan*/ ,char*) ; 
 struct clk* clk_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int clk_set_parent (struct clk*,struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ dmic_is_enabled (struct omap_dmic*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_dmic_select_fclk(struct omap_dmic *dmic, int clk_id,
				 unsigned int freq)
{
	struct clk *parent_clk, *mux;
	char *parent_clk_name;
	int ret = 0;

	switch (freq) {
	case 12000000:
	case 19200000:
	case 24000000:
	case 24576000:
		break;
	default:
		dev_err(dmic->dev, "invalid input frequency: %dHz\n", freq);
		dmic->fclk_freq = 0;
		return -EINVAL;
	}

	if (dmic->sysclk == clk_id) {
		dmic->fclk_freq = freq;
		return 0;
	}

	/* re-parent not allowed if a stream is ongoing */
	if (dmic->active && dmic_is_enabled(dmic)) {
		dev_err(dmic->dev, "can't re-parent when DMIC active\n");
		return -EBUSY;
	}

	switch (clk_id) {
	case OMAP_DMIC_SYSCLK_PAD_CLKS:
		parent_clk_name = "pad_clks_ck";
		break;
	case OMAP_DMIC_SYSCLK_SLIMBLUS_CLKS:
		parent_clk_name = "slimbus_clk";
		break;
	case OMAP_DMIC_SYSCLK_SYNC_MUX_CLKS:
		parent_clk_name = "dmic_sync_mux_ck";
		break;
	default:
		dev_err(dmic->dev, "fclk clk_id (%d) not supported\n", clk_id);
		return -EINVAL;
	}

	parent_clk = clk_get(dmic->dev, parent_clk_name);
	if (IS_ERR(parent_clk)) {
		dev_err(dmic->dev, "can't get %s\n", parent_clk_name);
		return -ENODEV;
	}

	mux = clk_get_parent(dmic->fclk);
	if (IS_ERR(mux)) {
		dev_err(dmic->dev, "can't get fck mux parent\n");
		clk_put(parent_clk);
		return -ENODEV;
	}

	mutex_lock(&dmic->mutex);
	if (dmic->active) {
		/* disable clock while reparenting */
		pm_runtime_put_sync(dmic->dev);
		ret = clk_set_parent(mux, parent_clk);
		pm_runtime_get_sync(dmic->dev);
	} else {
		ret = clk_set_parent(mux, parent_clk);
	}
	mutex_unlock(&dmic->mutex);

	if (ret < 0) {
		dev_err(dmic->dev, "re-parent failed\n");
		goto err_busy;
	}

	dmic->sysclk = clk_id;
	dmic->fclk_freq = freq;

err_busy:
	clk_put(mux);
	clk_put(parent_clk);

	return ret;
}