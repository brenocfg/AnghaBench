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
struct ext4_iloc {struct buffer_head* bh; } ;
struct ext4_dir_entry_2 {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_block; } ;

/* Variables and functions */
 int ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 TYPE_1__* ext4_raw_inode (struct ext4_iloc*) ; 

struct buffer_head *ext4_get_first_inline_block(struct inode *inode,
					struct ext4_dir_entry_2 **parent_de,
					int *retval)
{
	struct ext4_iloc iloc;

	*retval = ext4_get_inode_loc(inode, &iloc);
	if (*retval)
		return NULL;

	*parent_de = (struct ext4_dir_entry_2 *)ext4_raw_inode(&iloc)->i_block;

	return iloc.bh;
}