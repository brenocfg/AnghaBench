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
typedef  scalar_t__ uid_t ;
struct path {TYPE_1__* dentry; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ATTR_CTIME ; 
 int ATTR_GID ; 
 int ATTR_KILL_PRIV ; 
 int ATTR_KILL_SGID ; 
 int ATTR_KILL_SUID ; 
 int ATTR_UID ; 
 int EINVAL ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int break_deleg_wait (struct inode**) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,scalar_t__) ; 
 int notify_change (TYPE_1__*,struct iattr*,struct inode**) ; 
 int security_path_chown (struct path const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chown_common(const struct path *path, uid_t user, gid_t group)
{
	struct inode *inode = path->dentry->d_inode;
	struct inode *delegated_inode = NULL;
	int error;
	struct iattr newattrs;
	kuid_t uid;
	kgid_t gid;

	uid = make_kuid(current_user_ns(), user);
	gid = make_kgid(current_user_ns(), group);

retry_deleg:
	newattrs.ia_valid =  ATTR_CTIME;
	if (user != (uid_t) -1) {
		if (!uid_valid(uid))
			return -EINVAL;
		newattrs.ia_valid |= ATTR_UID;
		newattrs.ia_uid = uid;
	}
	if (group != (gid_t) -1) {
		if (!gid_valid(gid))
			return -EINVAL;
		newattrs.ia_valid |= ATTR_GID;
		newattrs.ia_gid = gid;
	}
	if (!S_ISDIR(inode->i_mode))
		newattrs.ia_valid |=
			ATTR_KILL_SUID | ATTR_KILL_SGID | ATTR_KILL_PRIV;
	inode_lock(inode);
	error = security_path_chown(path, uid, gid);
	if (!error)
		error = notify_change(path->dentry, &newattrs, &delegated_inode);
	inode_unlock(inode);
	if (delegated_inode) {
		error = break_deleg_wait(&delegated_inode);
		if (!error)
			goto retry_deleg;
	}
	return error;
}