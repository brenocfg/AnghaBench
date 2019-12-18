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
struct ext4_extent_idx {int /*<<< orphan*/  ei_leaf_hi; int /*<<< orphan*/  ei_leaf_lo; } ;
typedef  int ext4_fsblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (unsigned long) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned long) ; 

__attribute__((used)) static inline void ext4_idx_store_pblock(struct ext4_extent_idx *ix,
					 ext4_fsblk_t pb)
{
	ix->ei_leaf_lo = cpu_to_le32((unsigned long) (pb & 0xffffffff));
	ix->ei_leaf_hi = cpu_to_le16((unsigned long) ((pb >> 31) >> 1) &
				     0xffff);
}