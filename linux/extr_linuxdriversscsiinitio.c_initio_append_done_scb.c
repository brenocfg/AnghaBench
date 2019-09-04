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
struct scsi_ctrl_blk {struct scsi_ctrl_blk* next; int /*<<< orphan*/  status; } ;
struct initio_host {struct scsi_ctrl_blk* last_done; struct scsi_ctrl_blk* first_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_DONE ; 

__attribute__((used)) static void initio_append_done_scb(struct initio_host * host, struct scsi_ctrl_blk * scbp)
{
#if DEBUG_QUEUE
	printk("append done SCB %p; ", scbp);
#endif

	scbp->status = SCB_DONE;
	scbp->next = NULL;
	if (host->last_done != NULL) {
		host->last_done->next = scbp;
		host->last_done = scbp;
	} else {
		host->first_done = scbp;
		host->last_done = scbp;
	}
}