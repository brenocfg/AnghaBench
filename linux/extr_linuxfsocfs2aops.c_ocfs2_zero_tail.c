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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_sparse_alloc (int /*<<< orphan*/ ) ; 
 int ocfs2_zero_extend (struct inode*,struct buffer_head*,scalar_t__) ; 

__attribute__((used)) static int ocfs2_zero_tail(struct inode *inode, struct buffer_head *di_bh,
			   loff_t pos)
{
	int ret = 0;

	BUG_ON(!ocfs2_sparse_alloc(OCFS2_SB(inode->i_sb)));
	if (pos > i_size_read(inode))
		ret = ocfs2_zero_extend(inode, di_bh, pos);

	return ret;
}