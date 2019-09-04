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
struct scsi_ctrl_blk {struct scsi_ctrl_blk* next; } ;
struct initio_host {struct scsi_ctrl_blk* last_pending; struct scsi_ctrl_blk* first_pending; } ;

/* Variables and functions */

__attribute__((used)) static void initio_unlink_pend_scb(struct initio_host * host, struct scsi_ctrl_blk * scb)
{
	struct scsi_ctrl_blk *tmp, *prev;

#if DEBUG_QUEUE
	printk("unlink pend SCB %p; ", scb);
#endif

	prev = tmp = host->first_pending;
	while (tmp != NULL) {
		if (scb == tmp) {	/* Unlink this SCB              */
			if (tmp == host->first_pending) {
				if ((host->first_pending = tmp->next) == NULL)
					host->last_pending = NULL;
			} else {
				prev->next = tmp->next;
				if (tmp == host->last_pending)
					host->last_pending = prev;
			}
			tmp->next = NULL;
			break;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}