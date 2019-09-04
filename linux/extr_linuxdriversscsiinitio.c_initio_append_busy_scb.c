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
struct scsi_ctrl_blk {size_t target; struct scsi_ctrl_blk* next; int /*<<< orphan*/  status; scalar_t__ tagmsg; } ;
struct initio_host {struct scsi_ctrl_blk* last_busy; struct scsi_ctrl_blk* first_busy; TYPE_1__* targets; int /*<<< orphan*/ * act_tags; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_BUSY ; 
 int /*<<< orphan*/  TCF_BUSY ; 

__attribute__((used)) static void initio_append_busy_scb(struct initio_host * host, struct scsi_ctrl_blk * scbp)
{

#if DEBUG_QUEUE
	printk("append busy SCB %p; ", scbp);
#endif
	if (scbp->tagmsg)
		host->act_tags[scbp->target]++;
	else
		host->targets[scbp->target].flags |= TCF_BUSY;
	scbp->status = SCB_BUSY;
	scbp->next = NULL;
	if (host->last_busy != NULL) {
		host->last_busy->next = scbp;
		host->last_busy = scbp;
	} else {
		host->first_busy = scbp;
		host->last_busy = scbp;
	}
}