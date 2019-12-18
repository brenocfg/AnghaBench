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
struct sun4i_i2s {int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  mod_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_I2S_CTRL_GL_EN ; 
 int /*<<< orphan*/  SUN4I_I2S_CTRL_REG ; 
 int /*<<< orphan*/  SUN4I_I2S_CTRL_SDO_EN_MASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sun4i_i2s* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_i2s_runtime_suspend(struct device *dev)
{
	struct sun4i_i2s *i2s = dev_get_drvdata(dev);

	clk_disable_unprepare(i2s->mod_clk);

	/* Disable our output lines */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_SDO_EN_MASK, 0);

	/* Disable the whole hardware block */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_GL_EN, 0);

	regcache_cache_only(i2s->regmap, true);

	clk_disable_unprepare(i2s->bus_clk);

	return 0;
}