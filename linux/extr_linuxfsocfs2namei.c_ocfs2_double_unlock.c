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
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 

__attribute__((used)) static void ocfs2_double_unlock(struct inode *inode1, struct inode *inode2)
{
	ocfs2_inode_unlock(inode1, 1);

	if (inode1 != inode2)
		ocfs2_inode_unlock(inode2, 1);
}