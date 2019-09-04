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
struct hpsa_scsi_dev_t {scalar_t__ offload_to_be_enabled; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  offload_to_mirror; scalar_t__ offload_config; int /*<<< orphan*/  hba_ioaccel_enabled; int /*<<< orphan*/  ioaccel_handle; int /*<<< orphan*/  raid_map; int /*<<< orphan*/  raid_level; } ;
struct ctlr_info {TYPE_1__** dev; } ;
struct TYPE_2__ {scalar_t__ offload_enabled; scalar_t__ offload_to_be_enabled; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  offload_to_mirror; scalar_t__ offload_config; int /*<<< orphan*/  hba_ioaccel_enabled; int /*<<< orphan*/  ioaccel_handle; int /*<<< orphan*/  raid_map; int /*<<< orphan*/  raid_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HPSA_MAX_DEVICES ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  hpsa_show_dev_msg (int /*<<< orphan*/ ,struct ctlr_info*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void hpsa_scsi_update_entry(struct ctlr_info *h,
	int entry, struct hpsa_scsi_dev_t *new_entry)
{
	/* assumes h->devlock is held */
	BUG_ON(entry < 0 || entry >= HPSA_MAX_DEVICES);

	/* Raid level changed. */
	h->dev[entry]->raid_level = new_entry->raid_level;

	/*
	 * ioacccel_handle may have changed for a dual domain disk
	 */
	h->dev[entry]->ioaccel_handle = new_entry->ioaccel_handle;

	/* Raid offload parameters changed.  Careful about the ordering. */
	if (new_entry->offload_config && new_entry->offload_to_be_enabled) {
		/*
		 * if drive is newly offload_enabled, we want to copy the
		 * raid map data first.  If previously offload_enabled and
		 * offload_config were set, raid map data had better be
		 * the same as it was before. If raid map data has changed
		 * then it had better be the case that
		 * h->dev[entry]->offload_enabled is currently 0.
		 */
		h->dev[entry]->raid_map = new_entry->raid_map;
		h->dev[entry]->ioaccel_handle = new_entry->ioaccel_handle;
	}
	if (new_entry->offload_to_be_enabled) {
		h->dev[entry]->ioaccel_handle = new_entry->ioaccel_handle;
		wmb(); /* set ioaccel_handle *before* hba_ioaccel_enabled */
	}
	h->dev[entry]->hba_ioaccel_enabled = new_entry->hba_ioaccel_enabled;
	h->dev[entry]->offload_config = new_entry->offload_config;
	h->dev[entry]->offload_to_mirror = new_entry->offload_to_mirror;
	h->dev[entry]->queue_depth = new_entry->queue_depth;

	/*
	 * We can turn off ioaccel offload now, but need to delay turning
	 * ioaccel on until we can update h->dev[entry]->phys_disk[], but we
	 * can't do that until all the devices are updated.
	 */
	h->dev[entry]->offload_to_be_enabled = new_entry->offload_to_be_enabled;

	/*
	 * turn ioaccel off immediately if told to do so.
	 */
	if (!new_entry->offload_to_be_enabled)
		h->dev[entry]->offload_enabled = 0;

	hpsa_show_dev_msg(KERN_INFO, h, h->dev[entry], "updated");
}