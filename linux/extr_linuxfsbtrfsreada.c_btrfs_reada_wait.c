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
struct reada_control {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  elems; int /*<<< orphan*/  wait; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  reada_works_cnt; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reada_control_release ; 
 int /*<<< orphan*/  reada_start_machine (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

int btrfs_reada_wait(void *handle)
{
	struct reada_control *rc = handle;
	struct btrfs_fs_info *fs_info = rc->fs_info;

	while (atomic_read(&rc->elems)) {
		if (!atomic_read(&fs_info->reada_works_cnt))
			reada_start_machine(fs_info);
		wait_event_timeout(rc->wait, atomic_read(&rc->elems) == 0,
				   (HZ + 9) / 10);
	}

	kref_put(&rc->refcnt, reada_control_release);

	return 0;
}