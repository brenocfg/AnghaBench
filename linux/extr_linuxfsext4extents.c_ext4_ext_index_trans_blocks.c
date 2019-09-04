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
 scalar_t__ ext4_has_inline_data (struct inode*) ; 
 int ext_depth (struct inode*) ; 

int ext4_ext_index_trans_blocks(struct inode *inode, int extents)
{
	int index;
	int depth;

	/* If we are converting the inline data, only one is needed here. */
	if (ext4_has_inline_data(inode))
		return 1;

	depth = ext_depth(inode);

	if (extents <= 1)
		index = depth * 2;
	else
		index = depth * 3;

	return index;
}