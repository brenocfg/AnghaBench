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
struct inode {int /*<<< orphan*/  i_sb; scalar_t__ i_blocks; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {int b_size; } ;
typedef  int sector_t ;
typedef  int secno ;
struct TYPE_2__ {int mmu_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EIO ; 
 int ENOSPC ; 
 int hpfs_add_sector_to_btree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int hpfs_bmap (struct inode*,int,unsigned int*) ; 
 TYPE_1__* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  hpfs_lock (int /*<<< orphan*/ ) ; 
 int hpfs_search_hotfix_map (int /*<<< orphan*/ ,int) ; 
 unsigned int hpfs_search_hotfix_map_for_range (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  hpfs_truncate_btree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  hpfs_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hpfs_get_block(struct inode *inode, sector_t iblock, struct buffer_head *bh_result, int create)
{
	int r;
	secno s;
	unsigned n_secs;
	hpfs_lock(inode->i_sb);
	s = hpfs_bmap(inode, iblock, &n_secs);
	if (s) {
		if (bh_result->b_size >> 9 < n_secs)
			n_secs = bh_result->b_size >> 9;
		n_secs = hpfs_search_hotfix_map_for_range(inode->i_sb, s, n_secs);
		if (unlikely(!n_secs)) {
			s = hpfs_search_hotfix_map(inode->i_sb, s);
			n_secs = 1;
		}
		map_bh(bh_result, inode->i_sb, s);
		bh_result->b_size = n_secs << 9;
		goto ret_0;
	}
	if (!create) goto ret_0;
	if (iblock<<9 != hpfs_i(inode)->mmu_private) {
		BUG();
		r = -EIO;
		goto ret_r;
	}
	if ((s = hpfs_add_sector_to_btree(inode->i_sb, inode->i_ino, 1, inode->i_blocks - 1)) == -1) {
		hpfs_truncate_btree(inode->i_sb, inode->i_ino, 1, inode->i_blocks - 1);
		r = -ENOSPC;
		goto ret_r;
	}
	inode->i_blocks++;
	hpfs_i(inode)->mmu_private += 512;
	set_buffer_new(bh_result);
	map_bh(bh_result, inode->i_sb, hpfs_search_hotfix_map(inode->i_sb, s));
	ret_0:
	r = 0;
	ret_r:
	hpfs_unlock(inode->i_sb);
	return r;
}