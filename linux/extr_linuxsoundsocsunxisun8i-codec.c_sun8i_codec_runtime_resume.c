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
struct sun8i_codec {int /*<<< orphan*/  clk_module; int /*<<< orphan*/  clk_bus; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sun8i_codec* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun8i_codec_runtime_resume(struct device *dev)
{
	struct sun8i_codec *scodec = dev_get_drvdata(dev);
	int ret;

	ret = clk_prepare_enable(scodec->clk_module);
	if (ret) {
		dev_err(dev, "Failed to enable the module clock\n");
		return ret;
	}

	ret = clk_prepare_enable(scodec->clk_bus);
	if (ret) {
		dev_err(dev, "Failed to enable the bus clock\n");
		goto err_disable_modclk;
	}

	regcache_cache_only(scodec->regmap, false);

	ret = regcache_sync(scodec->regmap);
	if (ret) {
		dev_err(dev, "Failed to sync regmap cache\n");
		goto err_disable_clk;
	}

	return 0;

err_disable_clk:
	clk_disable_unprepare(scodec->clk_bus);

err_disable_modclk:
	clk_disable_unprepare(scodec->clk_module);

	return ret;
}