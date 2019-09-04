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
struct reserve_ticket {scalar_t__ bytes; int error; int /*<<< orphan*/  list; int /*<<< orphan*/  wait; } ;
struct btrfs_space_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  bytes_may_use; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int prepare_to_wait_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int wait_reserve_ticket(struct btrfs_fs_info *fs_info,
			       struct btrfs_space_info *space_info,
			       struct reserve_ticket *ticket, u64 orig_bytes)

{
	DEFINE_WAIT(wait);
	int ret = 0;

	spin_lock(&space_info->lock);
	while (ticket->bytes > 0 && ticket->error == 0) {
		ret = prepare_to_wait_event(&ticket->wait, &wait, TASK_KILLABLE);
		if (ret) {
			ret = -EINTR;
			break;
		}
		spin_unlock(&space_info->lock);

		schedule();

		finish_wait(&ticket->wait, &wait);
		spin_lock(&space_info->lock);
	}
	if (!ret)
		ret = ticket->error;
	if (!list_empty(&ticket->list))
		list_del_init(&ticket->list);
	if (ticket->bytes && ticket->bytes < orig_bytes) {
		u64 num_bytes = orig_bytes - ticket->bytes;
		space_info->bytes_may_use -= num_bytes;
		trace_btrfs_space_reservation(fs_info, "space_info",
					      space_info->flags, num_bytes, 0);
	}
	spin_unlock(&space_info->lock);

	return ret;
}