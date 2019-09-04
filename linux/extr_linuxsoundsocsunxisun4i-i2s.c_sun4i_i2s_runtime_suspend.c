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
struct sun4i_i2s {int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sun4i_i2s* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun4i_i2s_runtime_suspend(struct device *dev)
{
	struct sun4i_i2s *i2s = dev_get_drvdata(dev);

	regcache_cache_only(i2s->regmap, true);

	clk_disable_unprepare(i2s->bus_clk);

	return 0;
}