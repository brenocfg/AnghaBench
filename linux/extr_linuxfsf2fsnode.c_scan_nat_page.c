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
struct page {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_nm_info {int max_nid; int /*<<< orphan*/  nid_list_lock; int /*<<< orphan*/  nat_block_bitmap; } ;
struct f2fs_nat_block {TYPE_1__* entries; } ;
typedef  int nid_t ;
typedef  scalar_t__ block_t ;
struct TYPE_2__ {int /*<<< orphan*/  block_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NAT_BLOCK_OFFSET (int) ; 
 int NAT_ENTRY_PER_BLOCK ; 
 scalar_t__ NEW_ADDR ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 scalar_t__ NULL_ADDR ; 
 int /*<<< orphan*/  __set_bit_le (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_free_nid (struct f2fs_sb_info*,int,int,int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct f2fs_nat_block* page_address (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_free_nid_bitmap (struct f2fs_sb_info*,int,int,int) ; 

__attribute__((used)) static int scan_nat_page(struct f2fs_sb_info *sbi,
			struct page *nat_page, nid_t start_nid)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	struct f2fs_nat_block *nat_blk = page_address(nat_page);
	block_t blk_addr;
	unsigned int nat_ofs = NAT_BLOCK_OFFSET(start_nid);
	int i;

	__set_bit_le(nat_ofs, nm_i->nat_block_bitmap);

	i = start_nid % NAT_ENTRY_PER_BLOCK;

	for (; i < NAT_ENTRY_PER_BLOCK; i++, start_nid++) {
		if (unlikely(start_nid >= nm_i->max_nid))
			break;

		blk_addr = le32_to_cpu(nat_blk->entries[i].block_addr);

		if (blk_addr == NEW_ADDR)
			return -EINVAL;

		if (blk_addr == NULL_ADDR) {
			add_free_nid(sbi, start_nid, true, true);
		} else {
			spin_lock(&NM_I(sbi)->nid_list_lock);
			update_free_nid_bitmap(sbi, start_nid, false, true);
			spin_unlock(&NM_I(sbi)->nid_list_lock);
		}
	}

	return 0;
}