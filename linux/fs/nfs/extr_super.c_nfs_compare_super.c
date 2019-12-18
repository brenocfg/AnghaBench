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
struct super_block {int dummy; } ;
struct nfs_server {int flags; int /*<<< orphan*/  fsid; } ;
struct nfs_sb_mountdata {int mntflags; struct nfs_server* server; } ;

/* Variables and functions */
 int NFS_MOUNT_UNSHARED ; 
 struct nfs_server* NFS_SB (struct super_block*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int nfs_compare_mount_options (struct super_block*,struct nfs_server*,int) ; 
 int /*<<< orphan*/  nfs_compare_super_address (struct nfs_server*,struct nfs_server*) ; 
 int /*<<< orphan*/  nfs_compare_userns (struct nfs_server*,struct nfs_server*) ; 

__attribute__((used)) static int nfs_compare_super(struct super_block *sb, void *data)
{
	struct nfs_sb_mountdata *sb_mntdata = data;
	struct nfs_server *server = sb_mntdata->server, *old = NFS_SB(sb);
	int mntflags = sb_mntdata->mntflags;

	if (!nfs_compare_super_address(old, server))
		return 0;
	/* Note: NFS_MOUNT_UNSHARED == NFS4_MOUNT_UNSHARED */
	if (old->flags & NFS_MOUNT_UNSHARED)
		return 0;
	if (memcmp(&old->fsid, &server->fsid, sizeof(old->fsid)) != 0)
		return 0;
	if (!nfs_compare_userns(old, server))
		return 0;
	return nfs_compare_mount_options(sb, server, mntflags);
}