#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  link; } ;
struct TYPE_4__ {TYPE_1__ afs; } ;
struct file_lock {TYPE_2__ fl_u; int /*<<< orphan*/  fl_file; } ;
struct afs_vnode {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locks_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_fl_copy_lock(struct file_lock *new, struct file_lock *fl)
{
	struct afs_vnode *vnode = AFS_FS_I(locks_inode(fl->fl_file));

	_enter("");

	spin_lock(&vnode->lock);
	list_add(&new->fl_u.afs.link, &fl->fl_u.afs.link);
	spin_unlock(&vnode->lock);
}