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
struct reada_machine_work {int /*<<< orphan*/  work; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  reada_works_cnt; int /*<<< orphan*/  readahead_workers; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_readahead_helper ; 
 struct reada_machine_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reada_start_machine_worker ; 

__attribute__((used)) static void reada_start_machine(struct btrfs_fs_info *fs_info)
{
	struct reada_machine_work *rmw;

	rmw = kzalloc(sizeof(*rmw), GFP_KERNEL);
	if (!rmw) {
		/* FIXME we cannot handle this properly right now */
		BUG();
	}
	btrfs_init_work(&rmw->work, btrfs_readahead_helper,
			reada_start_machine_worker, NULL, NULL);
	rmw->fs_info = fs_info;

	btrfs_queue_work(fs_info->readahead_workers, &rmw->work);
	atomic_inc(&fs_info->reada_works_cnt);
}