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
struct vfsmount {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,struct vfsmount*) ; 
 struct vfsmount* afs_mntpt_do_automount (int /*<<< orphan*/ ) ; 
 int afs_mntpt_expiry_timeout ; 
 int /*<<< orphan*/  afs_mntpt_expiry_timer ; 
 int /*<<< orphan*/  afs_vfsmounts ; 
 int /*<<< orphan*/  afs_wq ; 
 int /*<<< orphan*/  mnt_set_expiry (struct vfsmount*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mntget (struct vfsmount*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

struct vfsmount *afs_d_automount(struct path *path)
{
	struct vfsmount *newmnt;

	_enter("{%pd}", path->dentry);

	newmnt = afs_mntpt_do_automount(path->dentry);
	if (IS_ERR(newmnt))
		return newmnt;

	mntget(newmnt); /* prevent immediate expiration */
	mnt_set_expiry(newmnt, &afs_vfsmounts);
	queue_delayed_work(afs_wq, &afs_mntpt_expiry_timer,
			   afs_mntpt_expiry_timeout * HZ);
	_leave(" = %p", newmnt);
	return newmnt;
}