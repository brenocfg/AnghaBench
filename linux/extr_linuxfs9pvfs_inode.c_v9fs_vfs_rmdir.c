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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_REMOVEDIR ; 
 int v9fs_remove (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 

int v9fs_vfs_rmdir(struct inode *i, struct dentry *d)
{
	return v9fs_remove(i, d, AT_REMOVEDIR);
}