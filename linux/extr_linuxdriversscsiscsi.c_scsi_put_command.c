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
struct scsi_cmnd {int /*<<< orphan*/  abort_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_del_cmd_from_list (struct scsi_cmnd*) ; 

void scsi_put_command(struct scsi_cmnd *cmd)
{
	scsi_del_cmd_from_list(cmd);
	BUG_ON(delayed_work_pending(&cmd->abort_work));
}