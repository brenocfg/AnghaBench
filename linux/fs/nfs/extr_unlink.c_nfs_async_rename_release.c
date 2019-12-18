#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct nfs_renamedata {int /*<<< orphan*/  cred; TYPE_1__* new_dir; TYPE_1__* old_dir; int /*<<< orphan*/  new_dentry; int /*<<< orphan*/  old_dentry; scalar_t__ cancelled; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_lock; struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ d_really_is_positive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct nfs_renamedata*) ; 
 int /*<<< orphan*/  nfs_force_lookup_revalidate (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_mark_for_revalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_sb_deactive (struct super_block*) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_async_rename_release(void *calldata)
{
	struct nfs_renamedata	*data = calldata;
	struct super_block *sb = data->old_dir->i_sb;

	if (d_really_is_positive(data->old_dentry))
		nfs_mark_for_revalidate(d_inode(data->old_dentry));

	/* The result of the rename is unknown. Play it safe by
	 * forcing a new lookup */
	if (data->cancelled) {
		spin_lock(&data->old_dir->i_lock);
		nfs_force_lookup_revalidate(data->old_dir);
		spin_unlock(&data->old_dir->i_lock);
		if (data->new_dir != data->old_dir) {
			spin_lock(&data->new_dir->i_lock);
			nfs_force_lookup_revalidate(data->new_dir);
			spin_unlock(&data->new_dir->i_lock);
		}
	}

	dput(data->old_dentry);
	dput(data->new_dentry);
	iput(data->old_dir);
	iput(data->new_dir);
	nfs_sb_deactive(sb);
	put_cred(data->cred);
	kfree(data);
}