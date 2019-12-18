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
struct o2hb_region {int /*<<< orphan*/  hr_dev_name; struct o2hb_disk_slot* hr_slots; } ;
struct o2hb_disk_slot {scalar_t__ ds_last_time; scalar_t__ ds_last_generation; scalar_t__ ds_node_num; struct o2hb_disk_heartbeat_block* ds_raw_block; } ;
struct o2hb_disk_heartbeat_block {scalar_t__ hb_node; int /*<<< orphan*/  hb_seq; int /*<<< orphan*/  hb_generation; } ;

/* Variables and functions */
 char* ERRSTR1 ; 
 char* ERRSTR2 ; 
 char* ERRSTR3 ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,scalar_t__,unsigned long long,unsigned long long,scalar_t__,unsigned long long,unsigned long long) ; 
 size_t o2nm_this_node () ; 

__attribute__((used)) static int o2hb_check_own_slot(struct o2hb_region *reg)
{
	struct o2hb_disk_slot *slot;
	struct o2hb_disk_heartbeat_block *hb_block;
	char *errstr;

	slot = &reg->hr_slots[o2nm_this_node()];
	/* Don't check on our 1st timestamp */
	if (!slot->ds_last_time)
		return 0;

	hb_block = slot->ds_raw_block;
	if (le64_to_cpu(hb_block->hb_seq) == slot->ds_last_time &&
	    le64_to_cpu(hb_block->hb_generation) == slot->ds_last_generation &&
	    hb_block->hb_node == slot->ds_node_num)
		return 1;

#define ERRSTR1		"Another node is heartbeating on device"
#define ERRSTR2		"Heartbeat generation mismatch on device"
#define ERRSTR3		"Heartbeat sequence mismatch on device"

	if (hb_block->hb_node != slot->ds_node_num)
		errstr = ERRSTR1;
	else if (le64_to_cpu(hb_block->hb_generation) !=
		 slot->ds_last_generation)
		errstr = ERRSTR2;
	else
		errstr = ERRSTR3;

	mlog(ML_ERROR, "%s (%s): expected(%u:0x%llx, 0x%llx), "
	     "ondisk(%u:0x%llx, 0x%llx)\n", errstr, reg->hr_dev_name,
	     slot->ds_node_num, (unsigned long long)slot->ds_last_generation,
	     (unsigned long long)slot->ds_last_time, hb_block->hb_node,
	     (unsigned long long)le64_to_cpu(hb_block->hb_generation),
	     (unsigned long long)le64_to_cpu(hb_block->hb_seq));

	return 0;
}