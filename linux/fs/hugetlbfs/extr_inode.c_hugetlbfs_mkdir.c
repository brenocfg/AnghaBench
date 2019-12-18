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
typedef  int umode_t ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int hugetlbfs_mknod (struct inode*,struct dentry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 

__attribute__((used)) static int hugetlbfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	int retval = hugetlbfs_mknod(dir, dentry, mode | S_IFDIR, 0);
	if (!retval)
		inc_nlink(dir);
	return retval;
}