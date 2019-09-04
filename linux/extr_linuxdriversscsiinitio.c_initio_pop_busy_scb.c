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
struct scsi_ctrl_blk {size_t target; scalar_t__ tagmsg; struct scsi_ctrl_blk* next; } ;
struct initio_host {TYPE_1__* targets; int /*<<< orphan*/ * act_tags; int /*<<< orphan*/ * last_busy; struct scsi_ctrl_blk* first_busy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCF_BUSY ; 

__attribute__((used)) static struct scsi_ctrl_blk *initio_pop_busy_scb(struct initio_host * host)
{
	struct scsi_ctrl_blk *tmp;


	if ((tmp = host->first_busy) != NULL) {
		if ((host->first_busy = tmp->next) == NULL)
			host->last_busy = NULL;
		tmp->next = NULL;
		if (tmp->tagmsg)
			host->act_tags[tmp->target]--;
		else
			host->targets[tmp->target].flags &= ~TCF_BUSY;
	}
#if DEBUG_QUEUE
	printk("Pop busy SCB %p; ", tmp);
#endif
	return tmp;
}