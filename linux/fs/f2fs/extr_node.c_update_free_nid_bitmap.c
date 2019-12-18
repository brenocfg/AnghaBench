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
struct f2fs_nm_info {int /*<<< orphan*/ * free_nid_count; int /*<<< orphan*/ * free_nid_bitmap; int /*<<< orphan*/  nat_block_bitmap; } ;
typedef  unsigned int nid_t ;

/* Variables and functions */
 unsigned int NAT_BLOCK_OFFSET (unsigned int) ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 unsigned int START_NID (unsigned int) ; 
 int /*<<< orphan*/  __clear_bit_le (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit_le (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit_le (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_free_nid_bitmap(struct f2fs_sb_info *sbi, nid_t nid,
							bool set, bool build)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	unsigned int nat_ofs = NAT_BLOCK_OFFSET(nid);
	unsigned int nid_ofs = nid - START_NID(nid);

	if (!test_bit_le(nat_ofs, nm_i->nat_block_bitmap))
		return;

	if (set) {
		if (test_bit_le(nid_ofs, nm_i->free_nid_bitmap[nat_ofs]))
			return;
		__set_bit_le(nid_ofs, nm_i->free_nid_bitmap[nat_ofs]);
		nm_i->free_nid_count[nat_ofs]++;
	} else {
		if (!test_bit_le(nid_ofs, nm_i->free_nid_bitmap[nat_ofs]))
			return;
		__clear_bit_le(nid_ofs, nm_i->free_nid_bitmap[nat_ofs]);
		if (!build)
			nm_i->free_nid_count[nat_ofs]--;
	}
}