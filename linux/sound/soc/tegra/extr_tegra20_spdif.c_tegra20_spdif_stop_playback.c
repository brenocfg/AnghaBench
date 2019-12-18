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
struct tegra20_spdif {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA20_SPDIF_CTRL ; 
 int /*<<< orphan*/  TEGRA20_SPDIF_CTRL_TX_EN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra20_spdif_stop_playback(struct tegra20_spdif *spdif)
{
	regmap_update_bits(spdif->regmap, TEGRA20_SPDIF_CTRL,
			   TEGRA20_SPDIF_CTRL_TX_EN, 0);
}