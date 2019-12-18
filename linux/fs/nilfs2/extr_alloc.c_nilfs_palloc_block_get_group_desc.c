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
struct nilfs_palloc_group_desc {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int bh_offset (struct buffer_head const*) ; 
 unsigned long nilfs_palloc_groups_per_desc_block (struct inode const*) ; 

__attribute__((used)) static struct nilfs_palloc_group_desc *
nilfs_palloc_block_get_group_desc(const struct inode *inode,
				  unsigned long group,
				  const struct buffer_head *bh, void *kaddr)
{
	return (struct nilfs_palloc_group_desc *)(kaddr + bh_offset(bh)) +
		group % nilfs_palloc_groups_per_desc_block(inode);
}