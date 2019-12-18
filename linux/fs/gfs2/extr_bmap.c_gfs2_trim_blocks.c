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
struct inode {int /*<<< orphan*/  i_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int do_shrink (struct inode*,int /*<<< orphan*/ ) ; 

void gfs2_trim_blocks(struct inode *inode)
{
	int ret;

	ret = do_shrink(inode, inode->i_size);
	WARN_ON(ret != 0);
}