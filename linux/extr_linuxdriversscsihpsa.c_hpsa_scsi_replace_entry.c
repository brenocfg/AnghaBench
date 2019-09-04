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
struct hpsa_scsi_dev_t {int target; int /*<<< orphan*/  lun; } ;
struct ctlr_info {struct hpsa_scsi_dev_t** dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HPSA_MAX_DEVICES ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  hpsa_show_dev_msg (int /*<<< orphan*/ ,struct ctlr_info*,struct hpsa_scsi_dev_t*,char*) ; 

__attribute__((used)) static void hpsa_scsi_replace_entry(struct ctlr_info *h,
	int entry, struct hpsa_scsi_dev_t *new_entry,
	struct hpsa_scsi_dev_t *added[], int *nadded,
	struct hpsa_scsi_dev_t *removed[], int *nremoved)
{
	/* assumes h->devlock is held */
	BUG_ON(entry < 0 || entry >= HPSA_MAX_DEVICES);
	removed[*nremoved] = h->dev[entry];
	(*nremoved)++;

	/*
	 * New physical devices won't have target/lun assigned yet
	 * so we need to preserve the values in the slot we are replacing.
	 */
	if (new_entry->target == -1) {
		new_entry->target = h->dev[entry]->target;
		new_entry->lun = h->dev[entry]->lun;
	}

	h->dev[entry] = new_entry;
	added[*nadded] = new_entry;
	(*nadded)++;

	hpsa_show_dev_msg(KERN_INFO, h, new_entry, "replaced");
}