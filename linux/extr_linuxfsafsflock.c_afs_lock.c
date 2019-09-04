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
struct file_lock {int /*<<< orphan*/  fl_type; scalar_t__ fl_end; scalar_t__ fl_start; int /*<<< orphan*/  fl_flags; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  vfs_inode; TYPE_1__ fid; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 int ENOLCK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 scalar_t__ IS_GETLK (int) ; 
 scalar_t__ __mandatory_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long,long long) ; 
 int afs_do_getlk (struct file*,struct file_lock*) ; 
 int afs_do_setlk (struct file*,struct file_lock*) ; 
 int afs_do_unlk (struct file*,struct file_lock*) ; 
 int /*<<< orphan*/  locks_inode (struct file*) ; 

int afs_lock(struct file *file, int cmd, struct file_lock *fl)
{
	struct afs_vnode *vnode = AFS_FS_I(locks_inode(file));

	_enter("{%x:%u},%d,{t=%x,fl=%x,r=%Ld:%Ld}",
	       vnode->fid.vid, vnode->fid.vnode, cmd,
	       fl->fl_type, fl->fl_flags,
	       (long long) fl->fl_start, (long long) fl->fl_end);

	/* AFS doesn't support mandatory locks */
	if (__mandatory_lock(&vnode->vfs_inode) && fl->fl_type != F_UNLCK)
		return -ENOLCK;

	if (IS_GETLK(cmd))
		return afs_do_getlk(file, fl);
	if (fl->fl_type == F_UNLCK)
		return afs_do_unlk(file, fl);
	return afs_do_setlk(file, fl);
}