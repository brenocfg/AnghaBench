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
struct f2fs_nm_info {unsigned int nat_blocks; int /*<<< orphan*/  nat_block_bitmap; int /*<<< orphan*/  full_nat_bits; int /*<<< orphan*/  nid_list_lock; int /*<<< orphan*/  empty_nat_bits; } ;
typedef  unsigned int nid_t ;

/* Variables and functions */
 unsigned int NAT_ENTRY_PER_BLOCK ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __set_bit_le (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enabled_nat_bits (struct f2fs_sb_info*,int /*<<< orphan*/ *) ; 
 unsigned int find_next_bit_le (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_free_nid_bitmap (struct f2fs_sb_info*,unsigned int,int,int) ; 

__attribute__((used)) static inline void load_free_nid_bitmap(struct f2fs_sb_info *sbi)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	unsigned int i = 0;
	nid_t nid, last_nid;

	if (!enabled_nat_bits(sbi, NULL))
		return;

	for (i = 0; i < nm_i->nat_blocks; i++) {
		i = find_next_bit_le(nm_i->empty_nat_bits, nm_i->nat_blocks, i);
		if (i >= nm_i->nat_blocks)
			break;

		__set_bit_le(i, nm_i->nat_block_bitmap);

		nid = i * NAT_ENTRY_PER_BLOCK;
		last_nid = nid + NAT_ENTRY_PER_BLOCK;

		spin_lock(&NM_I(sbi)->nid_list_lock);
		for (; nid < last_nid; nid++)
			update_free_nid_bitmap(sbi, nid, true, true);
		spin_unlock(&NM_I(sbi)->nid_list_lock);
	}

	for (i = 0; i < nm_i->nat_blocks; i++) {
		i = find_next_bit_le(nm_i->full_nat_bits, nm_i->nat_blocks, i);
		if (i >= nm_i->nat_blocks)
			break;

		__set_bit_le(i, nm_i->nat_block_bitmap);
	}
}