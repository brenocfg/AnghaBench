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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct superblock_security_struct {int flags; int behavior; scalar_t__ sid; scalar_t__ mntpoint_sid; scalar_t__ def_sid; int /*<<< orphan*/  isec_lock; int /*<<< orphan*/  isec_head; } ;
struct inode_security_struct {scalar_t__ initialized; scalar_t__ sclass; int /*<<< orphan*/  lock; scalar_t__ sid; scalar_t__ task_sid; int /*<<< orphan*/  list; } ;
struct inode {int i_opflags; int /*<<< orphan*/  i_mode; TYPE_1__* i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct superblock_security_struct* s_security; } ;

/* Variables and functions */
 int IOP_XATTR ; 
 scalar_t__ LABEL_INITIALIZED ; 
 scalar_t__ LABEL_INVALID ; 
 scalar_t__ LABEL_PENDING ; 
 scalar_t__ SECCLASS_FILE ; 
#define  SECURITY_FS_USE_MNTPOINT 132 
#define  SECURITY_FS_USE_NATIVE 131 
#define  SECURITY_FS_USE_TASK 130 
#define  SECURITY_FS_USE_TRANS 129 
#define  SECURITY_FS_USE_XATTR 128 
 int SE_SBGENFS ; 
 int SE_SBGENFS_XATTR ; 
 int SE_SBINITIALIZED ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 struct dentry* d_find_alias (struct inode*) ; 
 struct dentry* d_find_any_alias (struct inode*) ; 
 struct dentry* dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int inode_doinit_use_xattr (struct inode*,struct dentry*,scalar_t__,scalar_t__*) ; 
 scalar_t__ inode_mode_to_security_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int security_transition_sid (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int selinux_genfs_get_sid (struct dentry*,scalar_t__,int,scalar_t__*) ; 
 struct inode_security_struct* selinux_inode (struct inode*) ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inode_doinit_with_dentry(struct inode *inode, struct dentry *opt_dentry)
{
	struct superblock_security_struct *sbsec = NULL;
	struct inode_security_struct *isec = selinux_inode(inode);
	u32 task_sid, sid = 0;
	u16 sclass;
	struct dentry *dentry;
	int rc = 0;

	if (isec->initialized == LABEL_INITIALIZED)
		return 0;

	spin_lock(&isec->lock);
	if (isec->initialized == LABEL_INITIALIZED)
		goto out_unlock;

	if (isec->sclass == SECCLASS_FILE)
		isec->sclass = inode_mode_to_security_class(inode->i_mode);

	sbsec = inode->i_sb->s_security;
	if (!(sbsec->flags & SE_SBINITIALIZED)) {
		/* Defer initialization until selinux_complete_init,
		   after the initial policy is loaded and the security
		   server is ready to handle calls. */
		spin_lock(&sbsec->isec_lock);
		if (list_empty(&isec->list))
			list_add(&isec->list, &sbsec->isec_head);
		spin_unlock(&sbsec->isec_lock);
		goto out_unlock;
	}

	sclass = isec->sclass;
	task_sid = isec->task_sid;
	sid = isec->sid;
	isec->initialized = LABEL_PENDING;
	spin_unlock(&isec->lock);

	switch (sbsec->behavior) {
	case SECURITY_FS_USE_NATIVE:
		break;
	case SECURITY_FS_USE_XATTR:
		if (!(inode->i_opflags & IOP_XATTR)) {
			sid = sbsec->def_sid;
			break;
		}
		/* Need a dentry, since the xattr API requires one.
		   Life would be simpler if we could just pass the inode. */
		if (opt_dentry) {
			/* Called from d_instantiate or d_splice_alias. */
			dentry = dget(opt_dentry);
		} else {
			/*
			 * Called from selinux_complete_init, try to find a dentry.
			 * Some filesystems really want a connected one, so try
			 * that first.  We could split SECURITY_FS_USE_XATTR in
			 * two, depending upon that...
			 */
			dentry = d_find_alias(inode);
			if (!dentry)
				dentry = d_find_any_alias(inode);
		}
		if (!dentry) {
			/*
			 * this is can be hit on boot when a file is accessed
			 * before the policy is loaded.  When we load policy we
			 * may find inodes that have no dentry on the
			 * sbsec->isec_head list.  No reason to complain as these
			 * will get fixed up the next time we go through
			 * inode_doinit with a dentry, before these inodes could
			 * be used again by userspace.
			 */
			goto out;
		}

		rc = inode_doinit_use_xattr(inode, dentry, sbsec->def_sid,
					    &sid);
		dput(dentry);
		if (rc)
			goto out;
		break;
	case SECURITY_FS_USE_TASK:
		sid = task_sid;
		break;
	case SECURITY_FS_USE_TRANS:
		/* Default to the fs SID. */
		sid = sbsec->sid;

		/* Try to obtain a transition SID. */
		rc = security_transition_sid(&selinux_state, task_sid, sid,
					     sclass, NULL, &sid);
		if (rc)
			goto out;
		break;
	case SECURITY_FS_USE_MNTPOINT:
		sid = sbsec->mntpoint_sid;
		break;
	default:
		/* Default to the fs superblock SID. */
		sid = sbsec->sid;

		if ((sbsec->flags & SE_SBGENFS) && !S_ISLNK(inode->i_mode)) {
			/* We must have a dentry to determine the label on
			 * procfs inodes */
			if (opt_dentry) {
				/* Called from d_instantiate or
				 * d_splice_alias. */
				dentry = dget(opt_dentry);
			} else {
				/* Called from selinux_complete_init, try to
				 * find a dentry.  Some filesystems really want
				 * a connected one, so try that first.
				 */
				dentry = d_find_alias(inode);
				if (!dentry)
					dentry = d_find_any_alias(inode);
			}
			/*
			 * This can be hit on boot when a file is accessed
			 * before the policy is loaded.  When we load policy we
			 * may find inodes that have no dentry on the
			 * sbsec->isec_head list.  No reason to complain as
			 * these will get fixed up the next time we go through
			 * inode_doinit() with a dentry, before these inodes
			 * could be used again by userspace.
			 */
			if (!dentry)
				goto out;
			rc = selinux_genfs_get_sid(dentry, sclass,
						   sbsec->flags, &sid);
			if (rc) {
				dput(dentry);
				goto out;
			}

			if ((sbsec->flags & SE_SBGENFS_XATTR) &&
			    (inode->i_opflags & IOP_XATTR)) {
				rc = inode_doinit_use_xattr(inode, dentry,
							    sid, &sid);
				if (rc) {
					dput(dentry);
					goto out;
				}
			}
			dput(dentry);
		}
		break;
	}

out:
	spin_lock(&isec->lock);
	if (isec->initialized == LABEL_PENDING) {
		if (!sid || rc) {
			isec->initialized = LABEL_INVALID;
			goto out_unlock;
		}

		isec->initialized = LABEL_INITIALIZED;
		isec->sid = sid;
	}

out_unlock:
	spin_unlock(&isec->lock);
	return rc;
}