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
struct scsi_ctrl_blk {size_t target; struct scsi_ctrl_blk* next; scalar_t__ tagmsg; } ;
struct initio_host {TYPE_1__* targets; int /*<<< orphan*/ * act_tags; struct scsi_ctrl_blk* last_busy; struct scsi_ctrl_blk* first_busy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCF_BUSY ; 

__attribute__((used)) static void initio_unlink_busy_scb(struct initio_host * host, struct scsi_ctrl_blk * scb)
{
	struct scsi_ctrl_blk *tmp, *prev;

#if DEBUG_QUEUE
	printk("unlink busy SCB %p; ", scb);
#endif

	prev = tmp = host->first_busy;
	while (tmp != NULL) {
		if (scb == tmp) {	/* Unlink this SCB              */
			if (tmp == host->first_busy) {
				if ((host->first_busy = tmp->next) == NULL)
					host->last_busy = NULL;
			} else {
				prev->next = tmp->next;
				if (tmp == host->last_busy)
					host->last_busy = prev;
			}
			tmp->next = NULL;
			if (tmp->tagmsg)
				host->act_tags[tmp->target]--;
			else
				host->targets[tmp->target].flags &= ~TCF_BUSY;
			break;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return;
}