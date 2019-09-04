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
struct mesh_state {scalar_t__ phase; struct scsi_cmnd* request_qtail; struct scsi_cmnd* request_q; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;
struct TYPE_3__ {TYPE_2__* host; } ;

/* Variables and functions */
 scalar_t__ idle ; 
 int /*<<< orphan*/  mesh_start (struct mesh_state*) ; 

__attribute__((used)) static int mesh_queue_lck(struct scsi_cmnd *cmd, void (*done)(struct scsi_cmnd *))
{
	struct mesh_state *ms;

	cmd->scsi_done = done;
	cmd->host_scribble = NULL;

	ms = (struct mesh_state *) cmd->device->host->hostdata;

	if (ms->request_q == NULL)
		ms->request_q = cmd;
	else
		ms->request_qtail->host_scribble = (void *) cmd;
	ms->request_qtail = cmd;

	if (ms->phase == idle)
		mesh_start(ms);

	return 0;
}