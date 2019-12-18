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
struct node_info {scalar_t__ blk_addr; int /*<<< orphan*/  ino; int /*<<< orphan*/  nid; } ;
struct nat_entry {int /*<<< orphan*/  ni; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_nm_info {int /*<<< orphan*/  nat_tree_lock; } ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_FSYNCED_INODE ; 
 int /*<<< orphan*/  HAS_LAST_FSYNC ; 
 int /*<<< orphan*/  IS_CHECKPOINTED ; 
 scalar_t__ NEW_ADDR ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 scalar_t__ NULL_ADDR ; 
 struct nat_entry* __alloc_nat_entry (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __free_nat_entry (struct nat_entry*) ; 
 struct nat_entry* __init_nat_entry (struct f2fs_nm_info*,struct nat_entry*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __is_valid_data_blkaddr (scalar_t__) ; 
 struct nat_entry* __lookup_nat_cache (struct f2fs_nm_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_nat_cache_dirty (struct f2fs_nm_info*,struct nat_entry*) ; 
 int /*<<< orphan*/  copy_node_info (int /*<<< orphan*/ *,struct node_info*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  inc_node_version (unsigned char) ; 
 scalar_t__ nat_get_blkaddr (struct nat_entry*) ; 
 unsigned char nat_get_version (struct nat_entry*) ; 
 int /*<<< orphan*/  nat_set_blkaddr (struct nat_entry*,scalar_t__) ; 
 int /*<<< orphan*/  nat_set_version (struct nat_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nat_flag (struct nat_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_node_addr(struct f2fs_sb_info *sbi, struct node_info *ni,
			block_t new_blkaddr, bool fsync_done)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	struct nat_entry *e;
	struct nat_entry *new = __alloc_nat_entry(ni->nid, true);

	down_write(&nm_i->nat_tree_lock);
	e = __lookup_nat_cache(nm_i, ni->nid);
	if (!e) {
		e = __init_nat_entry(nm_i, new, NULL, true);
		copy_node_info(&e->ni, ni);
		f2fs_bug_on(sbi, ni->blk_addr == NEW_ADDR);
	} else if (new_blkaddr == NEW_ADDR) {
		/*
		 * when nid is reallocated,
		 * previous nat entry can be remained in nat cache.
		 * So, reinitialize it with new information.
		 */
		copy_node_info(&e->ni, ni);
		f2fs_bug_on(sbi, ni->blk_addr != NULL_ADDR);
	}
	/* let's free early to reduce memory consumption */
	if (e != new)
		__free_nat_entry(new);

	/* sanity check */
	f2fs_bug_on(sbi, nat_get_blkaddr(e) != ni->blk_addr);
	f2fs_bug_on(sbi, nat_get_blkaddr(e) == NULL_ADDR &&
			new_blkaddr == NULL_ADDR);
	f2fs_bug_on(sbi, nat_get_blkaddr(e) == NEW_ADDR &&
			new_blkaddr == NEW_ADDR);
	f2fs_bug_on(sbi, __is_valid_data_blkaddr(nat_get_blkaddr(e)) &&
			new_blkaddr == NEW_ADDR);

	/* increment version no as node is removed */
	if (nat_get_blkaddr(e) != NEW_ADDR && new_blkaddr == NULL_ADDR) {
		unsigned char version = nat_get_version(e);
		nat_set_version(e, inc_node_version(version));
	}

	/* change address */
	nat_set_blkaddr(e, new_blkaddr);
	if (!__is_valid_data_blkaddr(new_blkaddr))
		set_nat_flag(e, IS_CHECKPOINTED, false);
	__set_nat_cache_dirty(nm_i, e);

	/* update fsync_mark if its inode nat entry is still alive */
	if (ni->nid != ni->ino)
		e = __lookup_nat_cache(nm_i, ni->ino);
	if (e) {
		if (fsync_done && ni->nid == ni->ino)
			set_nat_flag(e, HAS_FSYNCED_INODE, true);
		set_nat_flag(e, HAS_LAST_FSYNC, fsync_done);
	}
	up_write(&nm_i->nat_tree_lock);
}