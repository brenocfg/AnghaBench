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
struct reserve_ticket {int error; scalar_t__ bytes; int /*<<< orphan*/  list; } ;
struct btrfs_space_info {int /*<<< orphan*/  lock; } ;
struct btrfs_fs_info {int dummy; } ;
typedef  enum btrfs_reserve_flush_enum { ____Placeholder_btrfs_reserve_flush_enum } btrfs_reserve_flush_enum ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
#define  BTRFS_RESERVE_FLUSH_ALL 130 
#define  BTRFS_RESERVE_FLUSH_EVICT 129 
#define  BTRFS_RESERVE_FLUSH_LIMIT 128 
 int ENOSPC ; 
 int /*<<< orphan*/  evict_flush_states ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  priority_flush_states ; 
 int /*<<< orphan*/  priority_reclaim_metadata_space (struct btrfs_fs_info*,struct btrfs_space_info*,struct reserve_ticket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_reserve_ticket (struct btrfs_fs_info*,struct btrfs_space_info*,struct reserve_ticket*) ; 

__attribute__((used)) static int handle_reserve_ticket(struct btrfs_fs_info *fs_info,
				 struct btrfs_space_info *space_info,
				 struct reserve_ticket *ticket,
				 enum btrfs_reserve_flush_enum flush)
{
	int ret;

	switch (flush) {
	case BTRFS_RESERVE_FLUSH_ALL:
		wait_reserve_ticket(fs_info, space_info, ticket);
		break;
	case BTRFS_RESERVE_FLUSH_LIMIT:
		priority_reclaim_metadata_space(fs_info, space_info, ticket,
						priority_flush_states,
						ARRAY_SIZE(priority_flush_states));
		break;
	case BTRFS_RESERVE_FLUSH_EVICT:
		priority_reclaim_metadata_space(fs_info, space_info, ticket,
						evict_flush_states,
						ARRAY_SIZE(evict_flush_states));
		break;
	default:
		ASSERT(0);
		break;
	}

	spin_lock(&space_info->lock);
	ret = ticket->error;
	if (ticket->bytes || ticket->error) {
		/*
		 * Need to delete here for priority tickets. For regular tickets
		 * either the async reclaim job deletes the ticket from the list
		 * or we delete it ourselves at wait_reserve_ticket().
		 */
		list_del_init(&ticket->list);
		if (!ret)
			ret = -ENOSPC;
	}
	spin_unlock(&space_info->lock);
	ASSERT(list_empty(&ticket->list));
	/*
	 * Check that we can't have an error set if the reservation succeeded,
	 * as that would confuse tasks and lead them to error out without
	 * releasing reserved space (if an error happens the expectation is that
	 * space wasn't reserved at all).
	 */
	ASSERT(!(ticket->bytes == 0 && ticket->error));
	return ret;
}