#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct btrfs_super_block {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  fs_state; int /*<<< orphan*/ * freed_extents; int /*<<< orphan*/ * pinned_extents; int /*<<< orphan*/  fs_roots_radix; int /*<<< orphan*/  buffer_radix; int /*<<< orphan*/  tree_mod_seq_list; int /*<<< orphan*/  dead_roots; int /*<<< orphan*/  dirty_qgroups; int /*<<< orphan*/  tree_mod_seq; int /*<<< orphan*/ * qgroup_ulist; int /*<<< orphan*/  qgroup_tree; int /*<<< orphan*/ * running_transaction; int /*<<< orphan*/  tree_mod_log_lock; int /*<<< orphan*/  qgroup_rescan_lock; int /*<<< orphan*/  qgroup_ioctl_lock; int /*<<< orphan*/  tree_mod_seq_lock; int /*<<< orphan*/  fs_roots_radix_lock; int /*<<< orphan*/  super_lock; int /*<<< orphan*/  qgroup_lock; int /*<<< orphan*/  buffer_lock; struct btrfs_fs_info* super_copy; struct btrfs_fs_info* fs_devices; int /*<<< orphan*/  subvol_srcu; void* sectorsize; void* nodesize; } ;
struct btrfs_fs_devices {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mnt_sb; } ;
struct TYPE_3__ {struct btrfs_fs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_STATE_DUMMY_FS_INFO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_TREE_FS_INFO_FREED_EXTENTS0 ; 
 int /*<<< orphan*/  IO_TREE_FS_INFO_FREED_EXTENTS1 ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_io_tree_init (struct btrfs_fs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ init_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct btrfs_fs_info*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* test_mnt ; 

struct btrfs_fs_info *btrfs_alloc_dummy_fs_info(u32 nodesize, u32 sectorsize)
{
	struct btrfs_fs_info *fs_info = kzalloc(sizeof(struct btrfs_fs_info),
						GFP_KERNEL);

	if (!fs_info)
		return fs_info;
	fs_info->fs_devices = kzalloc(sizeof(struct btrfs_fs_devices),
				      GFP_KERNEL);
	if (!fs_info->fs_devices) {
		kfree(fs_info);
		return NULL;
	}
	fs_info->super_copy = kzalloc(sizeof(struct btrfs_super_block),
				      GFP_KERNEL);
	if (!fs_info->super_copy) {
		kfree(fs_info->fs_devices);
		kfree(fs_info);
		return NULL;
	}

	fs_info->nodesize = nodesize;
	fs_info->sectorsize = sectorsize;

	if (init_srcu_struct(&fs_info->subvol_srcu)) {
		kfree(fs_info->fs_devices);
		kfree(fs_info->super_copy);
		kfree(fs_info);
		return NULL;
	}

	spin_lock_init(&fs_info->buffer_lock);
	spin_lock_init(&fs_info->qgroup_lock);
	spin_lock_init(&fs_info->super_lock);
	spin_lock_init(&fs_info->fs_roots_radix_lock);
	spin_lock_init(&fs_info->tree_mod_seq_lock);
	mutex_init(&fs_info->qgroup_ioctl_lock);
	mutex_init(&fs_info->qgroup_rescan_lock);
	rwlock_init(&fs_info->tree_mod_log_lock);
	fs_info->running_transaction = NULL;
	fs_info->qgroup_tree = RB_ROOT;
	fs_info->qgroup_ulist = NULL;
	atomic64_set(&fs_info->tree_mod_seq, 0);
	INIT_LIST_HEAD(&fs_info->dirty_qgroups);
	INIT_LIST_HEAD(&fs_info->dead_roots);
	INIT_LIST_HEAD(&fs_info->tree_mod_seq_list);
	INIT_RADIX_TREE(&fs_info->buffer_radix, GFP_ATOMIC);
	INIT_RADIX_TREE(&fs_info->fs_roots_radix, GFP_ATOMIC);
	extent_io_tree_init(fs_info, &fs_info->freed_extents[0],
			    IO_TREE_FS_INFO_FREED_EXTENTS0, NULL);
	extent_io_tree_init(fs_info, &fs_info->freed_extents[1],
			    IO_TREE_FS_INFO_FREED_EXTENTS1, NULL);
	fs_info->pinned_extents = &fs_info->freed_extents[0];
	set_bit(BTRFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state);

	test_mnt->mnt_sb->s_fs_info = fs_info;

	return fs_info;
}