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
struct super_block {scalar_t__ bd_fsfreeze_count; int s_mode; int s_flags; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_id; int /*<<< orphan*/  bd_fsfreeze_mutex; } ;
struct nilfs_super_data {int flags; struct super_block* bdev; scalar_t__ cno; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 struct dentry* ERR_CAST (struct super_block*) ; 
 struct dentry* ERR_PTR (int) ; 
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int PTR_ERR (struct super_block*) ; 
 int SB_ACTIVE ; 
 int SB_RDONLY ; 
 int SB_SILENT ; 
 struct super_block* blkdev_get_by_path (char const*,int,struct file_system_type*) ; 
 int /*<<< orphan*/  blkdev_put (struct super_block*,int) ; 
 int /*<<< orphan*/  block_size (struct super_block*) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nilfs_attach_snapshot (struct super_block*,scalar_t__,struct dentry**) ; 
 int nilfs_fill_super (struct super_block*,void*,int) ; 
 scalar_t__ nilfs_identify (char*,struct nilfs_super_data*) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,char*) ; 
 int nilfs_remount (struct super_block*,int*,void*) ; 
 int /*<<< orphan*/  nilfs_set_bdev_super ; 
 int /*<<< orphan*/  nilfs_test_bdev_super ; 
 scalar_t__ nilfs_tree_is_busy (int /*<<< orphan*/ ) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,int /*<<< orphan*/ ) ; 
 struct super_block* sget (struct file_system_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct super_block*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,struct super_block*) ; 

__attribute__((used)) static struct dentry *
nilfs_mount(struct file_system_type *fs_type, int flags,
	     const char *dev_name, void *data)
{
	struct nilfs_super_data sd;
	struct super_block *s;
	fmode_t mode = FMODE_READ | FMODE_EXCL;
	struct dentry *root_dentry;
	int err, s_new = false;

	if (!(flags & SB_RDONLY))
		mode |= FMODE_WRITE;

	sd.bdev = blkdev_get_by_path(dev_name, mode, fs_type);
	if (IS_ERR(sd.bdev))
		return ERR_CAST(sd.bdev);

	sd.cno = 0;
	sd.flags = flags;
	if (nilfs_identify((char *)data, &sd)) {
		err = -EINVAL;
		goto failed;
	}

	/*
	 * once the super is inserted into the list by sget, s_umount
	 * will protect the lockfs code from trying to start a snapshot
	 * while we are mounting
	 */
	mutex_lock(&sd.bdev->bd_fsfreeze_mutex);
	if (sd.bdev->bd_fsfreeze_count > 0) {
		mutex_unlock(&sd.bdev->bd_fsfreeze_mutex);
		err = -EBUSY;
		goto failed;
	}
	s = sget(fs_type, nilfs_test_bdev_super, nilfs_set_bdev_super, flags,
		 sd.bdev);
	mutex_unlock(&sd.bdev->bd_fsfreeze_mutex);
	if (IS_ERR(s)) {
		err = PTR_ERR(s);
		goto failed;
	}

	if (!s->s_root) {
		s_new = true;

		/* New superblock instance created */
		s->s_mode = mode;
		snprintf(s->s_id, sizeof(s->s_id), "%pg", sd.bdev);
		sb_set_blocksize(s, block_size(sd.bdev));

		err = nilfs_fill_super(s, data, flags & SB_SILENT ? 1 : 0);
		if (err)
			goto failed_super;

		s->s_flags |= SB_ACTIVE;
	} else if (!sd.cno) {
		if (nilfs_tree_is_busy(s->s_root)) {
			if ((flags ^ s->s_flags) & SB_RDONLY) {
				nilfs_msg(s, KERN_ERR,
					  "the device already has a %s mount.",
					  sb_rdonly(s) ? "read-only" : "read/write");
				err = -EBUSY;
				goto failed_super;
			}
		} else {
			/*
			 * Try remount to setup mount states if the current
			 * tree is not mounted and only snapshots use this sb.
			 */
			err = nilfs_remount(s, &flags, data);
			if (err)
				goto failed_super;
		}
	}

	if (sd.cno) {
		err = nilfs_attach_snapshot(s, sd.cno, &root_dentry);
		if (err)
			goto failed_super;
	} else {
		root_dentry = dget(s->s_root);
	}

	if (!s_new)
		blkdev_put(sd.bdev, mode);

	return root_dentry;

 failed_super:
	deactivate_locked_super(s);

 failed:
	if (!s_new)
		blkdev_put(sd.bdev, mode);
	return ERR_PTR(err);
}