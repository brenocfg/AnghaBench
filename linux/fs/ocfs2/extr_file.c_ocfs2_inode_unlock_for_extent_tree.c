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
struct TYPE_2__ {int /*<<< orphan*/  ip_alloc_sem; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_inode_unlock_for_extent_tree(struct inode *inode,
					       struct buffer_head **di_bh,
					       int meta_level,
					       int write_sem)
{
	if (write_sem)
		up_write(&OCFS2_I(inode)->ip_alloc_sem);
	else
		up_read(&OCFS2_I(inode)->ip_alloc_sem);

	brelse(*di_bh);
	*di_bh = NULL;

	if (meta_level >= 0)
		ocfs2_inode_unlock(inode, meta_level);
}