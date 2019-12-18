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
struct f2fs_nm_info {int /*<<< orphan*/  nat_bitmap_mir; int /*<<< orphan*/  nat_bitmap; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 unsigned int NAT_BLOCK_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_change_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_to_next_nat(struct f2fs_nm_info *nm_i, nid_t start_nid)
{
	unsigned int block_off = NAT_BLOCK_OFFSET(start_nid);

	f2fs_change_bit(block_off, nm_i->nat_bitmap);
#ifdef CONFIG_F2FS_CHECK_FS
	f2fs_change_bit(block_off, nm_i->nat_bitmap_mir);
#endif
}