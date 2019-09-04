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
typedef  enum tegra30_ahub_rxcif { ____Placeholder_tegra30_ahub_rxcif } tegra30_ahub_rxcif ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TEGRA30_AHUB_AUDIO_RX ; 
 int TEGRA30_AHUB_AUDIO_RX_STRIDE ; 
 int TEGRA30_AHUB_RXCIF_APBIF_RX0 ; 
 TYPE_1__* ahub ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra30_audio_write (int,int) ; 

int tegra30_ahub_set_rx_cif_source(enum tegra30_ahub_rxcif rxcif,
				   enum tegra30_ahub_txcif txcif)
{
	int channel = rxcif - TEGRA30_AHUB_RXCIF_APBIF_RX0;
	int reg;

	pm_runtime_get_sync(ahub->dev);

	reg = TEGRA30_AHUB_AUDIO_RX +
	      (channel * TEGRA30_AHUB_AUDIO_RX_STRIDE);
	tegra30_audio_write(reg, 1 << txcif);

	pm_runtime_put(ahub->dev);

	return 0;
}