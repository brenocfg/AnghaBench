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
struct TYPE_4__ {scalar_t__ phase; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__ SCp; } ;
struct aac_dev {scalar_t__ handle_pci_error; TYPE_3__* fibs; TYPE_2__* scsi_host_ptr; } ;
struct TYPE_6__ {scalar_t__ callback_data; } ;
struct TYPE_5__ {int can_queue; } ;

/* Variables and functions */
 scalar_t__ AAC_OWNER_FIRMWARE ; 
 int DID_NO_CONNECT ; 
 int DID_RESET ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void aac_flush_ios(struct aac_dev *aac)
{
	int i;
	struct scsi_cmnd *cmd;

	for (i = 0; i < aac->scsi_host_ptr->can_queue; i++) {
		cmd = (struct scsi_cmnd *)aac->fibs[i].callback_data;
		if (cmd && (cmd->SCp.phase == AAC_OWNER_FIRMWARE)) {
			scsi_dma_unmap(cmd);

			if (aac->handle_pci_error)
				cmd->result = DID_NO_CONNECT << 16;
			else
				cmd->result = DID_RESET << 16;

			cmd->scsi_done(cmd);
		}
	}
}