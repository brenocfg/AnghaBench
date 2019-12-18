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
struct nat_entry {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_nm_info {int /*<<< orphan*/  nat_tree_lock; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_FSYNCED_INODE ; 
 int /*<<< orphan*/  HAS_LAST_FSYNC ; 
 int /*<<< orphan*/  IS_CHECKPOINTED ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 struct nat_entry* __lookup_nat_cache (struct f2fs_nm_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ get_nat_flag (struct nat_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

bool f2fs_need_inode_block_update(struct f2fs_sb_info *sbi, nid_t ino)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	struct nat_entry *e;
	bool need_update = true;

	down_read(&nm_i->nat_tree_lock);
	e = __lookup_nat_cache(nm_i, ino);
	if (e && get_nat_flag(e, HAS_LAST_FSYNC) &&
			(get_nat_flag(e, IS_CHECKPOINTED) ||
			 get_nat_flag(e, HAS_FSYNCED_INODE)))
		need_update = false;
	up_read(&nm_i->nat_tree_lock);
	return need_update;
}