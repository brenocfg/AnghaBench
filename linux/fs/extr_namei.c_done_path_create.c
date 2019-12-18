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
struct path {int /*<<< orphan*/  mnt; TYPE_1__* dentry; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_drop_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 

void done_path_create(struct path *path, struct dentry *dentry)
{
	dput(dentry);
	inode_unlock(path->dentry->d_inode);
	mnt_drop_write(path->mnt);
	path_put(path);
}