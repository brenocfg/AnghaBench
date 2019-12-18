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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap_ahub; int /*<<< orphan*/  regmap_apbif; int /*<<< orphan*/  clk_d_audio; int /*<<< orphan*/  clk_apbif; } ;

/* Variables and functions */
 TYPE_1__* ahub ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tegra30_ahub_runtime_resume(struct device *dev)
{
	int ret;

	ret = clk_prepare_enable(ahub->clk_d_audio);
	if (ret) {
		dev_err(dev, "clk_enable d_audio failed: %d\n", ret);
		return ret;
	}
	ret = clk_prepare_enable(ahub->clk_apbif);
	if (ret) {
		dev_err(dev, "clk_enable apbif failed: %d\n", ret);
		clk_disable(ahub->clk_d_audio);
		return ret;
	}

	regcache_cache_only(ahub->regmap_apbif, false);
	regcache_cache_only(ahub->regmap_ahub, false);

	return 0;
}