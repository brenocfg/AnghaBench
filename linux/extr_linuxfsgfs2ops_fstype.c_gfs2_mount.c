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
struct super_block {scalar_t__ bd_fsfreeze_count; int s_mode; int s_flags; struct gfs2_sbd* s_fs_info; struct super_block* bd_super; int /*<<< orphan*/  s_id; scalar_t__ s_root; int /*<<< orphan*/  s_umount; int /*<<< orphan*/  bd_fsfreeze_mutex; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_root_dir; int /*<<< orphan*/  sd_master_dir; } ;
struct gfs2_args {int ar_commit; int ar_statfs_quantum; int ar_quota_quantum; scalar_t__ ar_meta; int /*<<< orphan*/  ar_errors; int /*<<< orphan*/  ar_data; int /*<<< orphan*/  ar_quota; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;
struct block_device {scalar_t__ bd_fsfreeze_count; int s_mode; int s_flags; struct gfs2_sbd* s_fs_info; struct block_device* bd_super; int /*<<< orphan*/  s_id; scalar_t__ s_root; int /*<<< orphan*/  s_umount; int /*<<< orphan*/  bd_fsfreeze_mutex; } ;
typedef  int fmode_t ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int EBUSY ; 
 struct dentry* ERR_CAST (struct super_block*) ; 
 struct dentry* ERR_PTR (int) ; 
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFS2_DATA_DEFAULT ; 
 int /*<<< orphan*/  GFS2_ERRORS_DEFAULT ; 
 int /*<<< orphan*/  GFS2_QUOTA_DEFAULT ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int PTR_ERR (struct super_block*) ; 
 int SB_ACTIVE ; 
 int SB_RDONLY ; 
 int SB_SILENT ; 
 struct super_block* blkdev_get_by_path (char const*,int,struct file_system_type*) ; 
 int /*<<< orphan*/  blkdev_put (struct super_block*,int) ; 
 int /*<<< orphan*/  block_size (struct super_block*) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int fill_super (struct super_block*,struct gfs2_args*,int) ; 
 int gfs2_mount_args (struct gfs2_args*,void*) ; 
 int /*<<< orphan*/  memset (struct gfs2_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gfs2_super ; 
 struct super_block* sget (struct file_system_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct super_block*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,struct super_block*) ; 
 int /*<<< orphan*/  test_gfs2_super ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *gfs2_mount(struct file_system_type *fs_type, int flags,
		       const char *dev_name, void *data)
{
	struct block_device *bdev;
	struct super_block *s;
	fmode_t mode = FMODE_READ | FMODE_EXCL;
	int error;
	struct gfs2_args args;
	struct gfs2_sbd *sdp;

	if (!(flags & SB_RDONLY))
		mode |= FMODE_WRITE;

	bdev = blkdev_get_by_path(dev_name, mode, fs_type);
	if (IS_ERR(bdev))
		return ERR_CAST(bdev);

	/*
	 * once the super is inserted into the list by sget, s_umount
	 * will protect the lockfs code from trying to start a snapshot
	 * while we are mounting
	 */
	mutex_lock(&bdev->bd_fsfreeze_mutex);
	if (bdev->bd_fsfreeze_count > 0) {
		mutex_unlock(&bdev->bd_fsfreeze_mutex);
		error = -EBUSY;
		goto error_bdev;
	}
	s = sget(fs_type, test_gfs2_super, set_gfs2_super, flags, bdev);
	mutex_unlock(&bdev->bd_fsfreeze_mutex);
	error = PTR_ERR(s);
	if (IS_ERR(s))
		goto error_bdev;

	if (s->s_root) {
		/*
		 * s_umount nests inside bd_mutex during
		 * __invalidate_device().  blkdev_put() acquires
		 * bd_mutex and can't be called under s_umount.  Drop
		 * s_umount temporarily.  This is safe as we're
		 * holding an active reference.
		 */
		up_write(&s->s_umount);
		blkdev_put(bdev, mode);
		down_write(&s->s_umount);
	} else {
		/* s_mode must be set before deactivate_locked_super calls */
		s->s_mode = mode;
	}

	memset(&args, 0, sizeof(args));
	args.ar_quota = GFS2_QUOTA_DEFAULT;
	args.ar_data = GFS2_DATA_DEFAULT;
	args.ar_commit = 30;
	args.ar_statfs_quantum = 30;
	args.ar_quota_quantum = 60;
	args.ar_errors = GFS2_ERRORS_DEFAULT;

	error = gfs2_mount_args(&args, data);
	if (error) {
		pr_warn("can't parse mount arguments\n");
		goto error_super;
	}

	if (s->s_root) {
		error = -EBUSY;
		if ((flags ^ s->s_flags) & SB_RDONLY)
			goto error_super;
	} else {
		snprintf(s->s_id, sizeof(s->s_id), "%pg", bdev);
		sb_set_blocksize(s, block_size(bdev));
		error = fill_super(s, &args, flags & SB_SILENT ? 1 : 0);
		if (error)
			goto error_super;
		s->s_flags |= SB_ACTIVE;
		bdev->bd_super = s;
	}

	sdp = s->s_fs_info;
	if (args.ar_meta)
		return dget(sdp->sd_master_dir);
	else
		return dget(sdp->sd_root_dir);

error_super:
	deactivate_locked_super(s);
	return ERR_PTR(error);
error_bdev:
	blkdev_put(bdev, mode);
	return ERR_PTR(error);
}