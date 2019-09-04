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
typedef  scalar_t__ u64 ;
struct o2nm_node {int dummy; } ;
struct o2hb_region {int /*<<< orphan*/  hr_live_node_bitmap; int /*<<< orphan*/  hr_dev_name; int /*<<< orphan*/  hr_block_bytes; struct o2hb_disk_heartbeat_block* hr_tmp_block; } ;
struct o2hb_node_event {int /*<<< orphan*/  hn_item; } ;
struct o2hb_disk_slot {size_t ds_node_num; unsigned int ds_equal_samples; scalar_t__ ds_last_time; scalar_t__ ds_last_generation; int /*<<< orphan*/  ds_changed_samples; int /*<<< orphan*/  ds_live_item; int /*<<< orphan*/  ds_raw_block; } ;
struct o2hb_disk_heartbeat_block {int /*<<< orphan*/  hb_dead_ms; int /*<<< orphan*/  hb_seq; int /*<<< orphan*/  hb_cksum; int /*<<< orphan*/  hb_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_HEARTBEAT ; 
 int /*<<< orphan*/  O2HB_LIVE_THRESHOLD ; 
 int /*<<< orphan*/  O2HB_NODE_DOWN_CB ; 
 int /*<<< orphan*/  O2HB_NODE_UP_CB ; 
 unsigned int O2HB_REGION_TIMEOUT_MS ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct o2hb_disk_heartbeat_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,size_t,...) ; 
 unsigned int o2hb_dead_threshold ; 
 int /*<<< orphan*/  o2hb_dump_slot (struct o2hb_disk_heartbeat_block*) ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  o2hb_live_node_bitmap ; 
 int /*<<< orphan*/ * o2hb_live_slots ; 
 int /*<<< orphan*/  o2hb_queue_node_event (struct o2hb_node_event*,int /*<<< orphan*/ ,struct o2nm_node*,size_t) ; 
 int /*<<< orphan*/  o2hb_run_event_list (struct o2hb_node_event*) ; 
 int /*<<< orphan*/  o2hb_verify_crc (struct o2hb_region*,struct o2hb_disk_heartbeat_block*) ; 
 struct o2nm_node* o2nm_get_node_by_num (size_t) ; 
 int /*<<< orphan*/  o2nm_node_put (struct o2nm_node*) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int test_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int o2hb_check_slot(struct o2hb_region *reg,
			   struct o2hb_disk_slot *slot)
{
	int changed = 0, gen_changed = 0;
	struct o2hb_node_event event =
		{ .hn_item = LIST_HEAD_INIT(event.hn_item), };
	struct o2nm_node *node;
	struct o2hb_disk_heartbeat_block *hb_block = reg->hr_tmp_block;
	u64 cputime;
	unsigned int dead_ms = o2hb_dead_threshold * O2HB_REGION_TIMEOUT_MS;
	unsigned int slot_dead_ms;
	int tmp;
	int queued = 0;

	memcpy(hb_block, slot->ds_raw_block, reg->hr_block_bytes);

	/*
	 * If a node is no longer configured but is still in the livemap, we
	 * may need to clear that bit from the livemap.
	 */
	node = o2nm_get_node_by_num(slot->ds_node_num);
	if (!node) {
		spin_lock(&o2hb_live_lock);
		tmp = test_bit(slot->ds_node_num, o2hb_live_node_bitmap);
		spin_unlock(&o2hb_live_lock);
		if (!tmp)
			return 0;
	}

	if (!o2hb_verify_crc(reg, hb_block)) {
		/* all paths from here will drop o2hb_live_lock for
		 * us. */
		spin_lock(&o2hb_live_lock);

		/* Don't print an error on the console in this case -
		 * a freshly formatted heartbeat area will not have a
		 * crc set on it. */
		if (list_empty(&slot->ds_live_item))
			goto out;

		/* The node is live but pushed out a bad crc. We
		 * consider it a transient miss but don't populate any
		 * other values as they may be junk. */
		mlog(ML_ERROR, "Node %d has written a bad crc to %s\n",
		     slot->ds_node_num, reg->hr_dev_name);
		o2hb_dump_slot(hb_block);

		slot->ds_equal_samples++;
		goto fire_callbacks;
	}

	/* we don't care if these wrap.. the state transitions below
	 * clear at the right places */
	cputime = le64_to_cpu(hb_block->hb_seq);
	if (slot->ds_last_time != cputime)
		slot->ds_changed_samples++;
	else
		slot->ds_equal_samples++;
	slot->ds_last_time = cputime;

	/* The node changed heartbeat generations. We assume this to
	 * mean it dropped off but came back before we timed out. We
	 * want to consider it down for the time being but don't want
	 * to lose any changed_samples state we might build up to
	 * considering it live again. */
	if (slot->ds_last_generation != le64_to_cpu(hb_block->hb_generation)) {
		gen_changed = 1;
		slot->ds_equal_samples = 0;
		mlog(ML_HEARTBEAT, "Node %d changed generation (0x%llx "
		     "to 0x%llx)\n", slot->ds_node_num,
		     (long long)slot->ds_last_generation,
		     (long long)le64_to_cpu(hb_block->hb_generation));
	}

	slot->ds_last_generation = le64_to_cpu(hb_block->hb_generation);

	mlog(ML_HEARTBEAT, "Slot %d gen 0x%llx cksum 0x%x "
	     "seq %llu last %llu changed %u equal %u\n",
	     slot->ds_node_num, (long long)slot->ds_last_generation,
	     le32_to_cpu(hb_block->hb_cksum),
	     (unsigned long long)le64_to_cpu(hb_block->hb_seq),
	     (unsigned long long)slot->ds_last_time, slot->ds_changed_samples,
	     slot->ds_equal_samples);

	spin_lock(&o2hb_live_lock);

fire_callbacks:
	/* dead nodes only come to life after some number of
	 * changes at any time during their dead time */
	if (list_empty(&slot->ds_live_item) &&
	    slot->ds_changed_samples >= O2HB_LIVE_THRESHOLD) {
		mlog(ML_HEARTBEAT, "Node %d (id 0x%llx) joined my region\n",
		     slot->ds_node_num, (long long)slot->ds_last_generation);

		set_bit(slot->ds_node_num, reg->hr_live_node_bitmap);

		/* first on the list generates a callback */
		if (list_empty(&o2hb_live_slots[slot->ds_node_num])) {
			mlog(ML_HEARTBEAT, "o2hb: Add node %d to live nodes "
			     "bitmap\n", slot->ds_node_num);
			set_bit(slot->ds_node_num, o2hb_live_node_bitmap);

			o2hb_queue_node_event(&event, O2HB_NODE_UP_CB, node,
					      slot->ds_node_num);

			changed = 1;
			queued = 1;
		}

		list_add_tail(&slot->ds_live_item,
			      &o2hb_live_slots[slot->ds_node_num]);

		slot->ds_equal_samples = 0;

		/* We want to be sure that all nodes agree on the
		 * number of milliseconds before a node will be
		 * considered dead. The self-fencing timeout is
		 * computed from this value, and a discrepancy might
		 * result in heartbeat calling a node dead when it
		 * hasn't self-fenced yet. */
		slot_dead_ms = le32_to_cpu(hb_block->hb_dead_ms);
		if (slot_dead_ms && slot_dead_ms != dead_ms) {
			/* TODO: Perhaps we can fail the region here. */
			mlog(ML_ERROR, "Node %d on device %s has a dead count "
			     "of %u ms, but our count is %u ms.\n"
			     "Please double check your configuration values "
			     "for 'O2CB_HEARTBEAT_THRESHOLD'\n",
			     slot->ds_node_num, reg->hr_dev_name, slot_dead_ms,
			     dead_ms);
		}
		goto out;
	}

	/* if the list is dead, we're done.. */
	if (list_empty(&slot->ds_live_item))
		goto out;

	/* live nodes only go dead after enough consequtive missed
	 * samples..  reset the missed counter whenever we see
	 * activity */
	if (slot->ds_equal_samples >= o2hb_dead_threshold || gen_changed) {
		mlog(ML_HEARTBEAT, "Node %d left my region\n",
		     slot->ds_node_num);

		clear_bit(slot->ds_node_num, reg->hr_live_node_bitmap);

		/* last off the live_slot generates a callback */
		list_del_init(&slot->ds_live_item);
		if (list_empty(&o2hb_live_slots[slot->ds_node_num])) {
			mlog(ML_HEARTBEAT, "o2hb: Remove node %d from live "
			     "nodes bitmap\n", slot->ds_node_num);
			clear_bit(slot->ds_node_num, o2hb_live_node_bitmap);

			/* node can be null */
			o2hb_queue_node_event(&event, O2HB_NODE_DOWN_CB,
					      node, slot->ds_node_num);

			changed = 1;
			queued = 1;
		}

		/* We don't clear this because the node is still
		 * actually writing new blocks. */
		if (!gen_changed)
			slot->ds_changed_samples = 0;
		goto out;
	}
	if (slot->ds_changed_samples) {
		slot->ds_changed_samples = 0;
		slot->ds_equal_samples = 0;
	}
out:
	spin_unlock(&o2hb_live_lock);

	if (queued)
		o2hb_run_event_list(&event);

	if (node)
		o2nm_node_put(node);
	return changed;
}