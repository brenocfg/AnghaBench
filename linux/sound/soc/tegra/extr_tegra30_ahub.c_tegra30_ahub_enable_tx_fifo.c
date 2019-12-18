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
typedef  enum tegra30_ahub_txcif { ____Placeholder_tegra30_ahub_txcif } tegra30_ahub_txcif ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TEGRA30_AHUB_CHANNEL_CTRL ; 
 int TEGRA30_AHUB_CHANNEL_CTRL_STRIDE ; 
 int TEGRA30_AHUB_CHANNEL_CTRL_TX_EN ; 
 int TEGRA30_AHUB_TXCIF_APBIF_TX0 ; 
 TYPE_1__* ahub ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int tegra30_apbif_read (int) ; 
 int /*<<< orphan*/  tegra30_apbif_write (int,int) ; 

int tegra30_ahub_enable_tx_fifo(enum tegra30_ahub_txcif txcif)
{
	int channel = txcif - TEGRA30_AHUB_TXCIF_APBIF_TX0;
	int reg, val;

	pm_runtime_get_sync(ahub->dev);

	reg = TEGRA30_AHUB_CHANNEL_CTRL +
	      (channel * TEGRA30_AHUB_CHANNEL_CTRL_STRIDE);
	val = tegra30_apbif_read(reg);
	val |= TEGRA30_AHUB_CHANNEL_CTRL_TX_EN;
	tegra30_apbif_write(reg, val);

	pm_runtime_put(ahub->dev);

	return 0;
}