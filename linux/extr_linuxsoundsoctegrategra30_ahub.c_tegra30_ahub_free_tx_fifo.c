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
struct TYPE_2__ {int /*<<< orphan*/  tx_usage; } ;

/* Variables and functions */
 int TEGRA30_AHUB_TXCIF_APBIF_TX0 ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* ahub ; 

int tegra30_ahub_free_tx_fifo(enum tegra30_ahub_txcif txcif)
{
	int channel = txcif - TEGRA30_AHUB_TXCIF_APBIF_TX0;

	__clear_bit(channel, ahub->tx_usage);

	return 0;
}