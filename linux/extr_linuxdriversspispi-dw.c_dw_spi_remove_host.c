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
struct dw_spi {int /*<<< orphan*/  master; int /*<<< orphan*/  irq; TYPE_1__* dma_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_exit ) (struct dw_spi*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dw_spi_debugfs_remove (struct dw_spi*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_shutdown_chip (struct dw_spi*) ; 
 int /*<<< orphan*/  stub1 (struct dw_spi*) ; 

void dw_spi_remove_host(struct dw_spi *dws)
{
	dw_spi_debugfs_remove(dws);

	if (dws->dma_ops && dws->dma_ops->dma_exit)
		dws->dma_ops->dma_exit(dws);

	spi_shutdown_chip(dws);

	free_irq(dws->irq, dws->master);
}