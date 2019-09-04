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
struct sym_ucmd {scalar_t__ eh_done; } ;
struct sym_hcb {int dummy; } ;
struct scsi_pointer {int dummy; } ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 struct sym_ucmd* SYM_UCMD_PTR (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

void sym_xpt_done(struct sym_hcb *np, struct scsi_cmnd *cmd)
{
	struct sym_ucmd *ucmd = SYM_UCMD_PTR(cmd);
	BUILD_BUG_ON(sizeof(struct scsi_pointer) < sizeof(struct sym_ucmd));

	if (ucmd->eh_done)
		complete(ucmd->eh_done);

	scsi_dma_unmap(cmd);
	cmd->scsi_done(cmd);
}