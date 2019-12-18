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
struct reserve_ticket {scalar_t__ bytes; int /*<<< orphan*/  wait; int /*<<< orphan*/  error; int /*<<< orphan*/  list; } ;
struct btrfs_space_info {int /*<<< orphan*/  lock; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int prepare_to_wait_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void wait_reserve_ticket(struct btrfs_fs_info *fs_info,
				struct btrfs_space_info *space_info,
				struct reserve_ticket *ticket)

{
	DEFINE_WAIT(wait);
	int ret = 0;

	spin_lock(&space_info->lock);
	while (ticket->bytes > 0 && ticket->error == 0) {
		ret = prepare_to_wait_event(&ticket->wait, &wait, TASK_KILLABLE);
		if (ret) {
			/*
			 * Delete us from the list. After we unlock the space
			 * info, we don't want the async reclaim job to reserve
			 * space for this ticket. If that would happen, then the
			 * ticket's task would not known that space was reserved
			 * despite getting an error, resulting in a space leak
			 * (bytes_may_use counter of our space_info).
			 */
			list_del_init(&ticket->list);
			ticket->error = -EINTR;
			break;
		}
		spin_unlock(&space_info->lock);

		schedule();

		finish_wait(&ticket->wait, &wait);
		spin_lock(&space_info->lock);
	}
	spin_unlock(&space_info->lock);
}