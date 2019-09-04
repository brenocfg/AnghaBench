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
struct the_nilfs {int /*<<< orphan*/  ns_snapshot_mount_mutex; int /*<<< orphan*/  ns_segctor_sem; int /*<<< orphan*/  ns_cpfile; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct nilfs_root {int dummy; } ;
struct dentry {int dummy; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nilfs_attach_checkpoint (struct super_block*,scalar_t__,int,struct nilfs_root**) ; 
 int nilfs_cpfile_is_snapshot (int /*<<< orphan*/ ,scalar_t__) ; 
 int nilfs_get_root_dentry (struct super_block*,struct nilfs_root*,struct dentry**) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  nilfs_put_root (struct nilfs_root*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_attach_snapshot(struct super_block *s, __u64 cno,
				 struct dentry **root_dentry)
{
	struct the_nilfs *nilfs = s->s_fs_info;
	struct nilfs_root *root;
	int ret;

	mutex_lock(&nilfs->ns_snapshot_mount_mutex);

	down_read(&nilfs->ns_segctor_sem);
	ret = nilfs_cpfile_is_snapshot(nilfs->ns_cpfile, cno);
	up_read(&nilfs->ns_segctor_sem);
	if (ret < 0) {
		ret = (ret == -ENOENT) ? -EINVAL : ret;
		goto out;
	} else if (!ret) {
		nilfs_msg(s, KERN_ERR,
			  "The specified checkpoint is not a snapshot (checkpoint number=%llu)",
			  (unsigned long long)cno);
		ret = -EINVAL;
		goto out;
	}

	ret = nilfs_attach_checkpoint(s, cno, false, &root);
	if (ret) {
		nilfs_msg(s, KERN_ERR,
			  "error %d while loading snapshot (checkpoint number=%llu)",
			  ret, (unsigned long long)cno);
		goto out;
	}
	ret = nilfs_get_root_dentry(s, root, root_dentry);
	nilfs_put_root(root);
 out:
	mutex_unlock(&nilfs->ns_snapshot_mount_mutex);
	return ret;
}