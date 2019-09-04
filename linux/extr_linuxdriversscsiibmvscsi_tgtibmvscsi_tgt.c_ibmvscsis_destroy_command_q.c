#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * base_addr; int /*<<< orphan*/  crq_token; } ;
struct scsi_info {int /*<<< orphan*/  state; TYPE_2__ cmd_q; TYPE_1__* dma_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  NO_QUEUE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void ibmvscsis_destroy_command_q(struct scsi_info *vscsi)
{
	dma_unmap_single(&vscsi->dma_dev->dev, vscsi->cmd_q.crq_token,
			 PAGE_SIZE, DMA_BIDIRECTIONAL);
	free_page((unsigned long)vscsi->cmd_q.base_addr);
	vscsi->cmd_q.base_addr = NULL;
	vscsi->state = NO_QUEUE;
}