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
 int __nfs_commit_inode (struct inode*,int,int /*<<< orphan*/ *) ; 

int nfs_commit_inode(struct inode *inode, int how)
{
	return __nfs_commit_inode(inode, how, NULL);
}