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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ocfs2_read_inode_block_full (struct inode*,struct buffer_head**,int /*<<< orphan*/ ) ; 

int ocfs2_read_inode_block(struct inode *inode, struct buffer_head **bh)
{
	return ocfs2_read_inode_block_full(inode, bh, 0);
}