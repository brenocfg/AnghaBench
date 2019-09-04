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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_nm_info {unsigned int nat_blocks; scalar_t__* nid_cnt; int /*<<< orphan*/  nat_tree_lock; int /*<<< orphan*/ * free_nid_bitmap; int /*<<< orphan*/ * free_nid_count; int /*<<< orphan*/  nat_block_bitmap; } ;
typedef  unsigned int nid_t ;

/* Variables and functions */
 size_t FREE_NID ; 
 scalar_t__ MAX_FREE_NIDS ; 
 unsigned int NAT_ENTRY_PER_BLOCK ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  add_free_nid (struct f2fs_sb_info*,unsigned int,int,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 unsigned int find_next_bit_le (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  scan_curseg_cache (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  test_bit_le (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scan_free_nid_bits(struct f2fs_sb_info *sbi)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	unsigned int i, idx;
	nid_t nid;

	down_read(&nm_i->nat_tree_lock);

	for (i = 0; i < nm_i->nat_blocks; i++) {
		if (!test_bit_le(i, nm_i->nat_block_bitmap))
			continue;
		if (!nm_i->free_nid_count[i])
			continue;
		for (idx = 0; idx < NAT_ENTRY_PER_BLOCK; idx++) {
			idx = find_next_bit_le(nm_i->free_nid_bitmap[i],
						NAT_ENTRY_PER_BLOCK, idx);
			if (idx >= NAT_ENTRY_PER_BLOCK)
				break;

			nid = i * NAT_ENTRY_PER_BLOCK + idx;
			add_free_nid(sbi, nid, true, false);

			if (nm_i->nid_cnt[FREE_NID] >= MAX_FREE_NIDS)
				goto out;
		}
	}
out:
	scan_curseg_cache(sbi);

	up_read(&nm_i->nat_tree_lock);
}