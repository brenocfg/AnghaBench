#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct nfs_mount_info {TYPE_1__* cloned; } ;
struct dentry {int dummy; } ;
struct TYPE_10__ {int caps; TYPE_3__* nfs_client; } ;
struct TYPE_9__ {scalar_t__ i_op; } ;
struct TYPE_8__ {TYPE_2__* rpc_ops; } ;
struct TYPE_7__ {scalar_t__ dir_inode_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int ESTALE ; 
 int NFS_CAP_SECURITY_LABEL ; 
 TYPE_5__* NFS_SB (struct super_block*) ; 
 unsigned long SECURITY_LSM_NATIVE_LABELS ; 
 TYPE_4__* d_inode (struct dentry*) ; 
 int security_sb_clone_mnt_opts (int /*<<< orphan*/ ,struct super_block*,unsigned long,unsigned long*) ; 

int nfs_clone_sb_security(struct super_block *s, struct dentry *mntroot,
			  struct nfs_mount_info *mount_info)
{
	int error;
	unsigned long kflags = 0, kflags_out = 0;

	/* clone any lsm security options from the parent to the new sb */
	if (d_inode(mntroot)->i_op != NFS_SB(s)->nfs_client->rpc_ops->dir_inode_ops)
		return -ESTALE;

	if (NFS_SB(s)->caps & NFS_CAP_SECURITY_LABEL)
		kflags |= SECURITY_LSM_NATIVE_LABELS;

	error = security_sb_clone_mnt_opts(mount_info->cloned->sb, s, kflags,
			&kflags_out);
	if (error)
		return error;

	if (NFS_SB(s)->caps & NFS_CAP_SECURITY_LABEL &&
		!(kflags_out & SECURITY_LSM_NATIVE_LABELS))
		NFS_SB(s)->caps &= ~NFS_CAP_SECURITY_LABEL;
	return 0;
}