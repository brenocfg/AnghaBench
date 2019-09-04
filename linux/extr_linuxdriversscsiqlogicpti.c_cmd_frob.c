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
struct scsi_cmnd {scalar_t__* cmnd; int /*<<< orphan*/  cmd_len; TYPE_3__* request; TYPE_2__* device; } ;
struct qlogicpti {scalar_t__* cmd_count; void** tag_ages; } ;
struct TYPE_4__ {int entry_cnt; int /*<<< orphan*/  entry_type; } ;
struct Command_Entry {size_t target_id; int time_out; int /*<<< orphan*/  cdb; int /*<<< orphan*/  control_flags; int /*<<< orphan*/  cdb_length; int /*<<< orphan*/  target_lun; TYPE_1__ hdr; } ;
struct TYPE_6__ {int timeout; } ;
struct TYPE_5__ {size_t id; scalar_t__ tagged_supported; int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFLAG_ORDERED_TAG ; 
 int /*<<< orphan*/  CFLAG_READ ; 
 int /*<<< orphan*/  CFLAG_SIMPLE_TAG ; 
 int /*<<< orphan*/  CFLAG_WRITE ; 
 int /*<<< orphan*/  ENTRY_COMMAND ; 
 int HZ ; 
 scalar_t__ WRITE_10 ; 
 scalar_t__ WRITE_12 ; 
 scalar_t__ WRITE_6 ; 
 void* jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct Command_Entry*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_after (void*,void*) ; 

__attribute__((used)) static inline void cmd_frob(struct Command_Entry *cmd, struct scsi_cmnd *Cmnd,
			    struct qlogicpti *qpti)
{
	memset(cmd, 0, sizeof(struct Command_Entry));
	cmd->hdr.entry_cnt = 1;
	cmd->hdr.entry_type = ENTRY_COMMAND;
	cmd->target_id = Cmnd->device->id;
	cmd->target_lun = Cmnd->device->lun;
	cmd->cdb_length = Cmnd->cmd_len;
	cmd->control_flags = 0;
	if (Cmnd->device->tagged_supported) {
		if (qpti->cmd_count[Cmnd->device->id] == 0)
			qpti->tag_ages[Cmnd->device->id] = jiffies;
		if (time_after(jiffies, qpti->tag_ages[Cmnd->device->id] + (5*HZ))) {
			cmd->control_flags = CFLAG_ORDERED_TAG;
			qpti->tag_ages[Cmnd->device->id] = jiffies;
		} else
			cmd->control_flags = CFLAG_SIMPLE_TAG;
	}
	if ((Cmnd->cmnd[0] == WRITE_6) ||
	    (Cmnd->cmnd[0] == WRITE_10) ||
	    (Cmnd->cmnd[0] == WRITE_12))
		cmd->control_flags |= CFLAG_WRITE;
	else
		cmd->control_flags |= CFLAG_READ;
	cmd->time_out = Cmnd->request->timeout/HZ;
	memcpy(cmd->cdb, Cmnd->cmnd, Cmnd->cmd_len);
}