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
struct f2fs_sb_info {int blocks_per_seg; } ;
struct f2fs_nm_info {int nat_blkaddr; int /*<<< orphan*/  nat_bitmap; } ;
typedef  int pgoff_t ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int NAT_BLOCK_OFFSET (int /*<<< orphan*/ ) ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline pgoff_t current_nat_addr(struct f2fs_sb_info *sbi, nid_t start)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	pgoff_t block_off;
	pgoff_t block_addr;

	/*
	 * block_off = segment_off * 512 + off_in_segment
	 * OLD = (segment_off * 512) * 2 + off_in_segment
	 * NEW = 2 * (segment_off * 512 + off_in_segment) - off_in_segment
	 */
	block_off = NAT_BLOCK_OFFSET(start);

	block_addr = (pgoff_t)(nm_i->nat_blkaddr +
		(block_off << 1) -
		(block_off & (sbi->blocks_per_seg - 1)));

	if (f2fs_test_bit(block_off, nm_i->nat_bitmap))
		block_addr += sbi->blocks_per_seg;

	return block_addr;
}