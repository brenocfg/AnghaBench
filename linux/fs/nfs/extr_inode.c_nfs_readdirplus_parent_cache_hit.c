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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CAP_READDIRPLUS ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  nfs_advise_use_readdirplus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_server_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_readdirplus_parent_cache_hit(struct dentry *dentry)
{
	struct dentry *parent;

	if (!nfs_server_capable(d_inode(dentry), NFS_CAP_READDIRPLUS))
		return;
	parent = dget_parent(dentry);
	nfs_advise_use_readdirplus(d_inode(parent));
	dput(parent);
}