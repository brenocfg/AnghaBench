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
struct initio_host {int /*<<< orphan*/ * last_done; struct scsi_ctrl_blk* first_done; } ;

/* Variables and functions */

struct scsi_ctrl_blk *initio_find_done_scb(struct initio_host * host)
{
	struct scsi_ctrl_blk *tmp;

	if ((tmp = host->first_done) != NULL) {
		if ((host->first_done = tmp->next) == NULL)
			host->last_done = NULL;
		tmp->next = NULL;
	}
#if DEBUG_QUEUE
	printk("find done SCB %p; ",tmp);
#endif
	return tmp;
}