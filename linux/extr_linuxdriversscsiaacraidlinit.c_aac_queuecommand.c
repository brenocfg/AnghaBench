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
struct TYPE_2__ {int /*<<< orphan*/  phase; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_OWNER_LOWLEVEL ; 
 int FAILED ; 
 scalar_t__ aac_scsi_cmd (struct scsi_cmnd*) ; 

__attribute__((used)) static int aac_queuecommand(struct Scsi_Host *shost,
			    struct scsi_cmnd *cmd)
{
	int r = 0;
	cmd->SCp.phase = AAC_OWNER_LOWLEVEL;
	r = (aac_scsi_cmd(cmd) ? FAILED : 0);
	return r;
}