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
typedef  int u16 ;
struct scsi_ctrl_blk {int lun; int target; struct scsi_ctrl_blk* next; } ;
struct initio_host {struct scsi_ctrl_blk* first_busy; } ;

/* Variables and functions */

struct scsi_ctrl_blk *initio_find_busy_scb(struct initio_host * host, u16 tarlun)
{
	struct scsi_ctrl_blk *tmp, *prev;
	u16 scbp_tarlun;


	prev = tmp = host->first_busy;
	while (tmp != NULL) {
		scbp_tarlun = (tmp->lun << 8) | (tmp->target);
		if (scbp_tarlun == tarlun) {	/* Unlink this SCB              */
			break;
		}
		prev = tmp;
		tmp = tmp->next;
	}
#if DEBUG_QUEUE
	printk("find busy SCB %p; ", tmp);
#endif
	return tmp;
}