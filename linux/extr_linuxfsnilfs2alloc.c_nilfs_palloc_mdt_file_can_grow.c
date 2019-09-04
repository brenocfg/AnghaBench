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
struct inode {int dummy; } ;

/* Variables and functions */
 unsigned long nilfs_palloc_groups_count (struct inode*) ; 
 unsigned long nilfs_palloc_groups_per_desc_block (struct inode*) ; 

__attribute__((used)) static inline bool nilfs_palloc_mdt_file_can_grow(struct inode *inode,
						    unsigned long desc_blocks)
{
	return (nilfs_palloc_groups_per_desc_block(inode) * desc_blocks) <
			nilfs_palloc_groups_count(inode);
}