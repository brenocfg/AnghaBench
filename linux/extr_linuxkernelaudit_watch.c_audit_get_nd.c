#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct path {struct dentry* dentry; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct audit_watch {int /*<<< orphan*/  ino; int /*<<< orphan*/  dev; int /*<<< orphan*/  path; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_ino; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 TYPE_2__* d_backing_inode (struct dentry*) ; 
 scalar_t__ d_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_unlock (TYPE_2__*) ; 
 struct dentry* kern_path_locked (int /*<<< orphan*/ ,struct path*) ; 

__attribute__((used)) static int audit_get_nd(struct audit_watch *watch, struct path *parent)
{
	struct dentry *d = kern_path_locked(watch->path, parent);
	if (IS_ERR(d))
		return PTR_ERR(d);
	inode_unlock(d_backing_inode(parent->dentry));
	if (d_is_positive(d)) {
		/* update watch filter fields */
		watch->dev = d->d_sb->s_dev;
		watch->ino = d_backing_inode(d)->i_ino;
	}
	dput(d);
	return 0;
}