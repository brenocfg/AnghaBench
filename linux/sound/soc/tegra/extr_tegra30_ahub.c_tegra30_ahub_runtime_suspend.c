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
struct TYPE_2__ {int /*<<< orphan*/  clk_d_audio; int /*<<< orphan*/  clk_apbif; int /*<<< orphan*/  regmap_ahub; int /*<<< orphan*/  regmap_apbif; } ;

/* Variables and functions */
 TYPE_1__* ahub ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tegra30_ahub_runtime_suspend(struct device *dev)
{
	regcache_cache_only(ahub->regmap_apbif, true);
	regcache_cache_only(ahub->regmap_ahub, true);

	clk_disable_unprepare(ahub->clk_apbif);
	clk_disable_unprepare(ahub->clk_d_audio);

	return 0;
}