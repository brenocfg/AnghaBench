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
struct file_lock {int fl_flags; int /*<<< orphan*/  fl_type; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_1__ fid; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 int ENOLCK ; 
 int FL_FLOCK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int afs_do_setlk (struct file*,struct file_lock*) ; 
 int afs_do_unlk (struct file*,struct file_lock*) ; 
 int /*<<< orphan*/  locks_inode (struct file*) ; 

int afs_flock(struct file *file, int cmd, struct file_lock *fl)
{
	struct afs_vnode *vnode = AFS_FS_I(locks_inode(file));

	_enter("{%x:%u},%d,{t=%x,fl=%x}",
	       vnode->fid.vid, vnode->fid.vnode, cmd,
	       fl->fl_type, fl->fl_flags);

	/*
	 * No BSD flocks over NFS allowed.
	 * Note: we could try to fake a POSIX lock request here by
	 * using ((u32) filp | 0x80000000) or some such as the pid.
	 * Not sure whether that would be unique, though, or whether
	 * that would break in other places.
	 */
	if (!(fl->fl_flags & FL_FLOCK))
		return -ENOLCK;

	/* we're simulating flock() locks using posix locks on the server */
	if (fl->fl_type == F_UNLCK)
		return afs_do_unlk(file, fl);
	return afs_do_setlk(file, fl);
}