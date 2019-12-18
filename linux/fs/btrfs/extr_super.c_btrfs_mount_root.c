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
struct super_block {int s_flags; scalar_t__ s_root; int /*<<< orphan*/  s_id; struct btrfs_fs_devices* fs_devices; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; struct btrfs_fs_devices* fs_devices; void* super_for_commit; void* super_copy; } ;
struct btrfs_fs_devices {scalar_t__ rw_devices; struct block_device* latest_bdev; } ;
struct btrfs_device {int s_flags; scalar_t__ s_root; int /*<<< orphan*/  s_id; struct btrfs_fs_devices* fs_devices; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct file_system_type* bdev_holder; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_CSUM_IMPL_FAST ; 
 int /*<<< orphan*/  BTRFS_SUPER_INFO_SIZE ; 
 int EACCES ; 
 int EBUSY ; 
 int ENOMEM ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  FMODE_READ ; 
 int /*<<< orphan*/  FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int PTR_ERR (struct super_block*) ; 
 int SB_NOSEC ; 
 int SB_RDONLY ; 
 int /*<<< orphan*/  btrfs_close_devices (struct btrfs_fs_devices*) ; 
 int btrfs_fill_super (struct super_block*,struct btrfs_fs_devices*,void*) ; 
 int btrfs_open_devices (struct btrfs_fs_devices*,int /*<<< orphan*/ ,struct file_system_type*) ; 
 int btrfs_parse_device_options (void*,int /*<<< orphan*/ ,struct file_system_type*) ; 
 TYPE_1__* btrfs_sb (struct super_block*) ; 
 struct super_block* btrfs_scan_one_device (char const*,int /*<<< orphan*/ ,struct file_system_type*) ; 
 int /*<<< orphan*/  btrfs_set_super ; 
 int /*<<< orphan*/  btrfs_test_super ; 
 int /*<<< orphan*/  crc32c_impl () ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 struct dentry* dget (scalar_t__) ; 
 int /*<<< orphan*/  free_fs_info (struct btrfs_fs_info*) ; 
 struct btrfs_fs_info* kvzalloc (int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_free_mnt_opts (void**) ; 
 int security_sb_eat_lsm_opts (void*,void**) ; 
 int security_sb_set_mnt_opts (struct super_block*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct super_block* sget (struct file_system_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,struct block_device*) ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uuid_mutex ; 

__attribute__((used)) static struct dentry *btrfs_mount_root(struct file_system_type *fs_type,
		int flags, const char *device_name, void *data)
{
	struct block_device *bdev = NULL;
	struct super_block *s;
	struct btrfs_device *device = NULL;
	struct btrfs_fs_devices *fs_devices = NULL;
	struct btrfs_fs_info *fs_info = NULL;
	void *new_sec_opts = NULL;
	fmode_t mode = FMODE_READ;
	int error = 0;

	if (!(flags & SB_RDONLY))
		mode |= FMODE_WRITE;

	if (data) {
		error = security_sb_eat_lsm_opts(data, &new_sec_opts);
		if (error)
			return ERR_PTR(error);
	}

	/*
	 * Setup a dummy root and fs_info for test/set super.  This is because
	 * we don't actually fill this stuff out until open_ctree, but we need
	 * it for searching for existing supers, so this lets us do that and
	 * then open_ctree will properly initialize everything later.
	 */
	fs_info = kvzalloc(sizeof(struct btrfs_fs_info), GFP_KERNEL);
	if (!fs_info) {
		error = -ENOMEM;
		goto error_sec_opts;
	}

	fs_info->super_copy = kzalloc(BTRFS_SUPER_INFO_SIZE, GFP_KERNEL);
	fs_info->super_for_commit = kzalloc(BTRFS_SUPER_INFO_SIZE, GFP_KERNEL);
	if (!fs_info->super_copy || !fs_info->super_for_commit) {
		error = -ENOMEM;
		goto error_fs_info;
	}

	mutex_lock(&uuid_mutex);
	error = btrfs_parse_device_options(data, mode, fs_type);
	if (error) {
		mutex_unlock(&uuid_mutex);
		goto error_fs_info;
	}

	device = btrfs_scan_one_device(device_name, mode, fs_type);
	if (IS_ERR(device)) {
		mutex_unlock(&uuid_mutex);
		error = PTR_ERR(device);
		goto error_fs_info;
	}

	fs_devices = device->fs_devices;
	fs_info->fs_devices = fs_devices;

	error = btrfs_open_devices(fs_devices, mode, fs_type);
	mutex_unlock(&uuid_mutex);
	if (error)
		goto error_fs_info;

	if (!(flags & SB_RDONLY) && fs_devices->rw_devices == 0) {
		error = -EACCES;
		goto error_close_devices;
	}

	bdev = fs_devices->latest_bdev;
	s = sget(fs_type, btrfs_test_super, btrfs_set_super, flags | SB_NOSEC,
		 fs_info);
	if (IS_ERR(s)) {
		error = PTR_ERR(s);
		goto error_close_devices;
	}

	if (s->s_root) {
		btrfs_close_devices(fs_devices);
		free_fs_info(fs_info);
		if ((flags ^ s->s_flags) & SB_RDONLY)
			error = -EBUSY;
	} else {
		snprintf(s->s_id, sizeof(s->s_id), "%pg", bdev);
		btrfs_sb(s)->bdev_holder = fs_type;
		if (!strstr(crc32c_impl(), "generic"))
			set_bit(BTRFS_FS_CSUM_IMPL_FAST, &fs_info->flags);
		error = btrfs_fill_super(s, fs_devices, data);
	}
	if (!error)
		error = security_sb_set_mnt_opts(s, new_sec_opts, 0, NULL);
	security_free_mnt_opts(&new_sec_opts);
	if (error) {
		deactivate_locked_super(s);
		return ERR_PTR(error);
	}

	return dget(s->s_root);

error_close_devices:
	btrfs_close_devices(fs_devices);
error_fs_info:
	free_fs_info(fs_info);
error_sec_opts:
	security_free_mnt_opts(&new_sec_opts);
	return ERR_PTR(error);
}