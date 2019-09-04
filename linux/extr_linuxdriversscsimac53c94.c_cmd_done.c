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
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct fsc_state {int /*<<< orphan*/  phase; struct scsi_cmnd* current_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  idle ; 
 int /*<<< orphan*/  mac53c94_start (struct fsc_state*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void cmd_done(struct fsc_state *state, int result)
{
	struct scsi_cmnd *cmd;

	cmd = state->current_req;
	if (cmd != 0) {
		cmd->result = result;
		(*cmd->scsi_done)(cmd);
		state->current_req = NULL;
	}
	state->phase = idle;
	mac53c94_start(state);
}