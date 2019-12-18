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
struct inode {TYPE_1__* i_sb; } ;
typedef  size_t loff_t ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */

__attribute__((used)) static int ocfs2_is_io_unaligned(struct inode *inode, size_t count, loff_t pos)
{
	int blockmask = inode->i_sb->s_blocksize - 1;
	loff_t final_size = pos + count;

	if ((pos & blockmask) || (final_size & blockmask))
		return 1;
	return 0;
}