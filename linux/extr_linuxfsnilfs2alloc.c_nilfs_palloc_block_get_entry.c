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
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {unsigned long mi_entries_per_block; unsigned long mi_entry_size; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode const*) ; 
 int bh_offset (struct buffer_head const*) ; 
 int /*<<< orphan*/  nilfs_palloc_group (struct inode const*,int /*<<< orphan*/ ,unsigned long*) ; 

void *nilfs_palloc_block_get_entry(const struct inode *inode, __u64 nr,
				   const struct buffer_head *bh, void *kaddr)
{
	unsigned long entry_offset, group_offset;

	nilfs_palloc_group(inode, nr, &group_offset);
	entry_offset = group_offset % NILFS_MDT(inode)->mi_entries_per_block;

	return kaddr + bh_offset(bh) +
		entry_offset * NILFS_MDT(inode)->mi_entry_size;
}