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
struct list_head {int dummy; } ;
struct fsync_inode_entry {int dummy; } ;
struct f2fs_sb_info {TYPE_1__* sb; int /*<<< orphan*/  cp_mutex; } ;
struct cp_control {int /*<<< orphan*/  reason; } ;
typedef  int loff_t ;
struct TYPE_2__ {unsigned long s_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_RECOVERY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ MAIN_BLKADDR (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  META_MAPPING (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  NODE_MAPPING (struct f2fs_sb_info*) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  SBI_IS_RECOVERED ; 
 int /*<<< orphan*/  SBI_POR_DOING ; 
 unsigned long SB_ACTIVE ; 
 unsigned long SB_RDONLY ; 
 int /*<<< orphan*/  clear_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_fsync_dnodes (struct list_head*,int) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int f2fs_enable_quota_files (struct f2fs_sb_info*,unsigned long) ; 
 int /*<<< orphan*/  f2fs_info (struct f2fs_sb_info*,char*) ; 
 int /*<<< orphan*/  f2fs_kmem_cache_create (char*,int) ; 
 int /*<<< orphan*/  f2fs_quota_off_umount (TYPE_1__*) ; 
 int f2fs_write_checkpoint (struct f2fs_sb_info*,struct cp_control*) ; 
 int find_fsync_dnodes (struct f2fs_sb_info*,struct list_head*,int) ; 
 int /*<<< orphan*/  fsync_entry_slab ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int recover_data (struct f2fs_sb_info*,struct list_head*,struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages_range (int /*<<< orphan*/ ,int,int) ; 

int f2fs_recover_fsync_data(struct f2fs_sb_info *sbi, bool check_only)
{
	struct list_head inode_list, tmp_inode_list;
	struct list_head dir_list;
	int err;
	int ret = 0;
	unsigned long s_flags = sbi->sb->s_flags;
	bool need_writecp = false;
#ifdef CONFIG_QUOTA
	int quota_enabled;
#endif

	if (s_flags & SB_RDONLY) {
		f2fs_info(sbi, "recover fsync data on readonly fs");
		sbi->sb->s_flags &= ~SB_RDONLY;
	}

#ifdef CONFIG_QUOTA
	/* Needed for iput() to work correctly and not trash data */
	sbi->sb->s_flags |= SB_ACTIVE;
	/* Turn on quotas so that they are updated correctly */
	quota_enabled = f2fs_enable_quota_files(sbi, s_flags & SB_RDONLY);
#endif

	fsync_entry_slab = f2fs_kmem_cache_create("f2fs_fsync_inode_entry",
			sizeof(struct fsync_inode_entry));
	if (!fsync_entry_slab) {
		err = -ENOMEM;
		goto out;
	}

	INIT_LIST_HEAD(&inode_list);
	INIT_LIST_HEAD(&tmp_inode_list);
	INIT_LIST_HEAD(&dir_list);

	/* prevent checkpoint */
	mutex_lock(&sbi->cp_mutex);

	/* step #1: find fsynced inode numbers */
	err = find_fsync_dnodes(sbi, &inode_list, check_only);
	if (err || list_empty(&inode_list))
		goto skip;

	if (check_only) {
		ret = 1;
		goto skip;
	}

	need_writecp = true;

	/* step #2: recover data */
	err = recover_data(sbi, &inode_list, &tmp_inode_list, &dir_list);
	if (!err)
		f2fs_bug_on(sbi, !list_empty(&inode_list));
	else {
		/* restore s_flags to let iput() trash data */
		sbi->sb->s_flags = s_flags;
	}
skip:
	destroy_fsync_dnodes(&inode_list, err);
	destroy_fsync_dnodes(&tmp_inode_list, err);

	/* truncate meta pages to be used by the recovery */
	truncate_inode_pages_range(META_MAPPING(sbi),
			(loff_t)MAIN_BLKADDR(sbi) << PAGE_SHIFT, -1);

	if (err) {
		truncate_inode_pages_final(NODE_MAPPING(sbi));
		truncate_inode_pages_final(META_MAPPING(sbi));
	} else {
		clear_sbi_flag(sbi, SBI_POR_DOING);
	}
	mutex_unlock(&sbi->cp_mutex);

	/* let's drop all the directory inodes for clean checkpoint */
	destroy_fsync_dnodes(&dir_list, err);

	if (need_writecp) {
		set_sbi_flag(sbi, SBI_IS_RECOVERED);

		if (!err) {
			struct cp_control cpc = {
				.reason = CP_RECOVERY,
			};
			err = f2fs_write_checkpoint(sbi, &cpc);
		}
	}

	kmem_cache_destroy(fsync_entry_slab);
out:
#ifdef CONFIG_QUOTA
	/* Turn quotas off */
	if (quota_enabled)
		f2fs_quota_off_umount(sbi->sb);
#endif
	sbi->sb->s_flags = s_flags; /* Restore SB_RDONLY status */

	return ret ? ret: err;
}