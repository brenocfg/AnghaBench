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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {unsigned long mi_entries_per_block; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode const*) ; 
 unsigned long nilfs_palloc_bitmap_blkoff (struct inode const*,unsigned long) ; 
 unsigned long nilfs_palloc_group (struct inode const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static unsigned long
nilfs_palloc_entry_blkoff(const struct inode *inode, __u64 nr)
{
	unsigned long group, group_offset;

	group = nilfs_palloc_group(inode, nr, &group_offset);

	return nilfs_palloc_bitmap_blkoff(inode, group) + 1 +
		group_offset / NILFS_MDT(inode)->mi_entries_per_block;
}