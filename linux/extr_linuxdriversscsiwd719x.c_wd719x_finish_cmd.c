#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wd719x_scb {int /*<<< orphan*/  list; } ;
struct wd719x {TYPE_1__* pdev; int /*<<< orphan*/  free_scbs; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_handle; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_2__ SCp; scalar_t__ host_scribble; TYPE_3__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  host; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 struct wd719x* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void wd719x_finish_cmd(struct scsi_cmnd *cmd, int result)
{
	struct wd719x *wd = shost_priv(cmd->device->host);
	struct wd719x_scb *scb = (struct wd719x_scb *) cmd->host_scribble;

	if (scb) {
		list_move(&scb->list, &wd->free_scbs);
		dma_unmap_single(&wd->pdev->dev, cmd->SCp.dma_handle,
				 SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
		scsi_dma_unmap(cmd);
	}
	cmd->result = result << 16;
	cmd->scsi_done(cmd);
}