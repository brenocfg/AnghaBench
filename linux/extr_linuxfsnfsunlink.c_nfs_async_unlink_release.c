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
struct super_block {int dummy; } ;
struct nfs_unlinkdata {struct dentry* dentry; } ;
struct dentry {int /*<<< orphan*/  d_parent; struct super_block* d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  rmdir_sem; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_lookup_done (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  nfs_free_unlinkdata (struct nfs_unlinkdata*) ; 
 int /*<<< orphan*/  nfs_sb_deactive (struct super_block*) ; 
 int /*<<< orphan*/  up_read_non_owner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_async_unlink_release(void *calldata)
{
	struct nfs_unlinkdata	*data = calldata;
	struct dentry *dentry = data->dentry;
	struct super_block *sb = dentry->d_sb;

	up_read_non_owner(&NFS_I(d_inode(dentry->d_parent))->rmdir_sem);
	d_lookup_done(dentry);
	nfs_free_unlinkdata(data);
	dput(dentry);
	nfs_sb_deactive(sb);
}