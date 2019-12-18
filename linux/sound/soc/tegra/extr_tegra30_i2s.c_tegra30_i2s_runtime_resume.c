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
struct tegra30_i2s {int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk_i2s; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct tegra30_i2s* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tegra30_i2s_runtime_resume(struct device *dev)
{
	struct tegra30_i2s *i2s = dev_get_drvdata(dev);
	int ret;

	ret = clk_prepare_enable(i2s->clk_i2s);
	if (ret) {
		dev_err(dev, "clk_enable failed: %d\n", ret);
		return ret;
	}

	regcache_cache_only(i2s->regmap, false);

	return 0;
}