#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_5__ {int i_mode; } ;

/* Variables and functions */
#define  S_IFDIR 128 
 int S_IFMT ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_rmdir (TYPE_1__*,struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_unlink (TYPE_1__*,struct dentry*) ; 
 scalar_t__ simple_positive (struct dentry*) ; 
 int simple_rmdir (TYPE_1__*,struct dentry*) ; 
 int /*<<< orphan*/  simple_unlink (TYPE_1__*,struct dentry*) ; 

__attribute__((used)) static int __tracefs_remove(struct dentry *dentry, struct dentry *parent)
{
	int ret = 0;

	if (simple_positive(dentry)) {
		if (dentry->d_inode) {
			dget(dentry);
			switch (dentry->d_inode->i_mode & S_IFMT) {
			case S_IFDIR:
				ret = simple_rmdir(parent->d_inode, dentry);
				if (!ret)
					fsnotify_rmdir(parent->d_inode, dentry);
				break;
			default:
				simple_unlink(parent->d_inode, dentry);
				fsnotify_unlink(parent->d_inode, dentry);
				break;
			}
			if (!ret)
				d_delete(dentry);
			dput(dentry);
		}
	}
	return ret;
}