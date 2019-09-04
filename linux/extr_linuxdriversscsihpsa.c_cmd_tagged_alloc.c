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
struct scsi_cmnd {int dummy; } ;
struct ctlr_info {int nr_cmds; TYPE_1__* pdev; struct CommandList* cmd_pool; } ;
struct CommandList {struct scsi_cmnd* scsi_cmd; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int HPSA_NRESERVED_CMDS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  hpsa_cmd_partial_init (struct ctlr_info*,int,struct CommandList*) ; 
 int hpsa_get_cmd_index (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  hpsa_is_cmd_idle (struct CommandList*) ; 
 int /*<<< orphan*/  scsi_print_command (struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct CommandList *cmd_tagged_alloc(struct ctlr_info *h,
					    struct scsi_cmnd *scmd)
{
	int idx = hpsa_get_cmd_index(scmd);
	struct CommandList *c = h->cmd_pool + idx;

	if (idx < HPSA_NRESERVED_CMDS || idx >= h->nr_cmds) {
		dev_err(&h->pdev->dev, "Bad block tag: %d not in [%d..%d]\n",
			idx, HPSA_NRESERVED_CMDS, h->nr_cmds - 1);
		/* The index value comes from the block layer, so if it's out of
		 * bounds, it's probably not our bug.
		 */
		BUG();
	}

	atomic_inc(&c->refcount);
	if (unlikely(!hpsa_is_cmd_idle(c))) {
		/*
		 * We expect that the SCSI layer will hand us a unique tag
		 * value.  Thus, there should never be a collision here between
		 * two requests...because if the selected command isn't idle
		 * then someone is going to be very disappointed.
		 */
		dev_err(&h->pdev->dev,
			"tag collision (tag=%d) in cmd_tagged_alloc().\n",
			idx);
		if (c->scsi_cmd != NULL)
			scsi_print_command(c->scsi_cmd);
		scsi_print_command(scmd);
	}

	hpsa_cmd_partial_init(h, idx, c);
	return c;
}