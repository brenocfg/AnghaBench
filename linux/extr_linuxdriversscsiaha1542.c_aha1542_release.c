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
struct Scsi_Host {int dma_channel; scalar_t__ n_io_port; scalar_t__ io_port; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_dma (int) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct Scsi_Host*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static int aha1542_release(struct Scsi_Host *sh)
{
	scsi_remove_host(sh);
	if (sh->dma_channel != 0xff)
		free_dma(sh->dma_channel);
	if (sh->irq)
		free_irq(sh->irq, sh);
	if (sh->io_port && sh->n_io_port)
		release_region(sh->io_port, sh->n_io_port);
	scsi_host_put(sh);
	return 0;
}