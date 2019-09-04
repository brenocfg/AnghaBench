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
typedef  scalar_t__ u64 ;
struct reserve_ticket {scalar_t__ bytes; int /*<<< orphan*/  list; int /*<<< orphan*/  wait; scalar_t__ error; } ;
struct btrfs_space_info {scalar_t__ total_bytes; int flags; int flush; int /*<<< orphan*/  lock; int /*<<< orphan*/  bytes_may_use; int /*<<< orphan*/  priority_tickets; int /*<<< orphan*/  tickets; } ;
struct btrfs_fs_info {int /*<<< orphan*/  async_reclaim_work; int /*<<< orphan*/  flags; } ;
typedef  enum btrfs_reserve_flush_enum { ____Placeholder_btrfs_reserve_flush_enum } btrfs_reserve_flush_enum ;
struct TYPE_2__ {int /*<<< orphan*/  journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BTRFS_BLOCK_GROUP_METADATA ; 
 int /*<<< orphan*/  BTRFS_FS_LOG_RECOVERING ; 
 int BTRFS_RESERVE_FLUSH_ALL ; 
 int BTRFS_RESERVE_NO_FLUSH ; 
 int ENOSPC ; 
 scalar_t__ btrfs_space_info_used (struct btrfs_space_info*,int) ; 
 scalar_t__ can_overcommit (struct btrfs_fs_info*,struct btrfs_space_info*,scalar_t__,int,int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ need_do_async_reclaim (struct btrfs_fs_info*,struct btrfs_space_info*,scalar_t__,int) ; 
 int /*<<< orphan*/  priority_reclaim_metadata_space (struct btrfs_fs_info*,struct btrfs_space_info*,struct reserve_ticket*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  trace_btrfs_trigger_flush (struct btrfs_fs_info*,int,scalar_t__,int,char*) ; 
 int wait_reserve_ticket (struct btrfs_fs_info*,struct btrfs_space_info*,struct reserve_ticket*,scalar_t__) ; 
 int /*<<< orphan*/  work_busy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __reserve_metadata_bytes(struct btrfs_fs_info *fs_info,
				    struct btrfs_space_info *space_info,
				    u64 orig_bytes,
				    enum btrfs_reserve_flush_enum flush,
				    bool system_chunk)
{
	struct reserve_ticket ticket;
	u64 used;
	int ret = 0;

	ASSERT(orig_bytes);
	ASSERT(!current->journal_info || flush != BTRFS_RESERVE_FLUSH_ALL);

	spin_lock(&space_info->lock);
	ret = -ENOSPC;
	used = btrfs_space_info_used(space_info, true);

	/*
	 * If we have enough space then hooray, make our reservation and carry
	 * on.  If not see if we can overcommit, and if we can, hooray carry on.
	 * If not things get more complicated.
	 */
	if (used + orig_bytes <= space_info->total_bytes) {
		space_info->bytes_may_use += orig_bytes;
		trace_btrfs_space_reservation(fs_info, "space_info",
					      space_info->flags, orig_bytes, 1);
		ret = 0;
	} else if (can_overcommit(fs_info, space_info, orig_bytes, flush,
				  system_chunk)) {
		space_info->bytes_may_use += orig_bytes;
		trace_btrfs_space_reservation(fs_info, "space_info",
					      space_info->flags, orig_bytes, 1);
		ret = 0;
	}

	/*
	 * If we couldn't make a reservation then setup our reservation ticket
	 * and kick the async worker if it's not already running.
	 *
	 * If we are a priority flusher then we just need to add our ticket to
	 * the list and we will do our own flushing further down.
	 */
	if (ret && flush != BTRFS_RESERVE_NO_FLUSH) {
		ticket.bytes = orig_bytes;
		ticket.error = 0;
		init_waitqueue_head(&ticket.wait);
		if (flush == BTRFS_RESERVE_FLUSH_ALL) {
			list_add_tail(&ticket.list, &space_info->tickets);
			if (!space_info->flush) {
				space_info->flush = 1;
				trace_btrfs_trigger_flush(fs_info,
							  space_info->flags,
							  orig_bytes, flush,
							  "enospc");
				queue_work(system_unbound_wq,
					   &fs_info->async_reclaim_work);
			}
		} else {
			list_add_tail(&ticket.list,
				      &space_info->priority_tickets);
		}
	} else if (!ret && space_info->flags & BTRFS_BLOCK_GROUP_METADATA) {
		used += orig_bytes;
		/*
		 * We will do the space reservation dance during log replay,
		 * which means we won't have fs_info->fs_root set, so don't do
		 * the async reclaim as we will panic.
		 */
		if (!test_bit(BTRFS_FS_LOG_RECOVERING, &fs_info->flags) &&
		    need_do_async_reclaim(fs_info, space_info,
					  used, system_chunk) &&
		    !work_busy(&fs_info->async_reclaim_work)) {
			trace_btrfs_trigger_flush(fs_info, space_info->flags,
						  orig_bytes, flush, "preempt");
			queue_work(system_unbound_wq,
				   &fs_info->async_reclaim_work);
		}
	}
	spin_unlock(&space_info->lock);
	if (!ret || flush == BTRFS_RESERVE_NO_FLUSH)
		return ret;

	if (flush == BTRFS_RESERVE_FLUSH_ALL)
		return wait_reserve_ticket(fs_info, space_info, &ticket,
					   orig_bytes);

	ret = 0;
	priority_reclaim_metadata_space(fs_info, space_info, &ticket);
	spin_lock(&space_info->lock);
	if (ticket.bytes) {
		if (ticket.bytes < orig_bytes) {
			u64 num_bytes = orig_bytes - ticket.bytes;
			space_info->bytes_may_use -= num_bytes;
			trace_btrfs_space_reservation(fs_info, "space_info",
						      space_info->flags,
						      num_bytes, 0);

		}
		list_del_init(&ticket.list);
		ret = -ENOSPC;
	}
	spin_unlock(&space_info->lock);
	ASSERT(list_empty(&ticket.list));
	return ret;
}