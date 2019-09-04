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
struct tegra_spi_data {int /*<<< orphan*/  is_curr_dma_xfer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  handle_cpu_based_xfer (struct tegra_spi_data*) ; 
 int /*<<< orphan*/  handle_dma_based_xfer (struct tegra_spi_data*) ; 

__attribute__((used)) static irqreturn_t tegra_spi_isr_thread(int irq, void *context_data)
{
	struct tegra_spi_data *tspi = context_data;

	if (!tspi->is_curr_dma_xfer)
		return handle_cpu_based_xfer(tspi);
	return handle_dma_based_xfer(tspi);
}