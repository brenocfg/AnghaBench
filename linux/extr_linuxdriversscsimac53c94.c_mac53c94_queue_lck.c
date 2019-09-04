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
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/ * host_scribble; TYPE_1__* device; } ;
struct fsc_state {scalar_t__ phase; struct scsi_cmnd* request_qtail; struct scsi_cmnd* request_q; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;
struct TYPE_3__ {TYPE_2__* host; } ;

/* Variables and functions */
 scalar_t__ idle ; 
 int /*<<< orphan*/  mac53c94_start (struct fsc_state*) ; 

__attribute__((used)) static int mac53c94_queue_lck(struct scsi_cmnd *cmd, void (*done)(struct scsi_cmnd *))
{
	struct fsc_state *state;

#if 0
	if (cmd->sc_data_direction == DMA_TO_DEVICE) {
		int i;
		printk(KERN_DEBUG "mac53c94_queue %p: command is", cmd);
		for (i = 0; i < cmd->cmd_len; ++i)
			printk(KERN_CONT " %.2x", cmd->cmnd[i]);
		printk(KERN_CONT "\n");
		printk(KERN_DEBUG "use_sg=%d request_bufflen=%d request_buffer=%p\n",
		       scsi_sg_count(cmd), scsi_bufflen(cmd), scsi_sglist(cmd));
	}
#endif

	cmd->scsi_done = done;
	cmd->host_scribble = NULL;

	state = (struct fsc_state *) cmd->device->host->hostdata;

	if (state->request_q == NULL)
		state->request_q = cmd;
	else
		state->request_qtail->host_scribble = (void *) cmd;
	state->request_qtail = cmd;

	if (state->phase == idle)
		mac53c94_start(state);

	return 0;
}