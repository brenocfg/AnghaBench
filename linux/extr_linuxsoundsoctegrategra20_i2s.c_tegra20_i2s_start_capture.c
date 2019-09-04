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
struct tegra20_i2s {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA20_I2S_CTRL ; 
 int /*<<< orphan*/  TEGRA20_I2S_CTRL_FIFO2_ENABLE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra20_i2s_start_capture(struct tegra20_i2s *i2s)
{
	regmap_update_bits(i2s->regmap, TEGRA20_I2S_CTRL,
			   TEGRA20_I2S_CTRL_FIFO2_ENABLE,
			   TEGRA20_I2S_CTRL_FIFO2_ENABLE);
}