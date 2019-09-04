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
struct gelic_wl_info {int /*<<< orphan*/  eurus_cmd_queue; } ;
struct gelic_eurus_cmd {unsigned int cmd; unsigned int buf_size; int /*<<< orphan*/  done; int /*<<< orphan*/  work; struct gelic_wl_info* wl; void* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelic_eurus_sync_cmd_worker ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct gelic_eurus_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct gelic_eurus_cmd *gelic_eurus_sync_cmd(struct gelic_wl_info *wl,
						    unsigned int eurus_cmd,
						    void *buffer,
						    unsigned int buf_size)
{
	struct gelic_eurus_cmd *cmd;

	/* allocate cmd */
	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return NULL;

	/* initialize members */
	cmd->cmd = eurus_cmd;
	cmd->buffer = buffer;
	cmd->buf_size = buf_size;
	cmd->wl = wl;
	INIT_WORK(&cmd->work, gelic_eurus_sync_cmd_worker);
	init_completion(&cmd->done);
	queue_work(wl->eurus_cmd_queue, &cmd->work);

	/* wait for command completion */
	wait_for_completion(&cmd->done);

	return cmd;
}