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
struct file {int dummy; } ;

/* Variables and functions */
 long EIO ; 
 long ENOSPC ; 
 long ENOTTY ; 
#define  F2FS_IOC_ABORT_VOLATILE_WRITE 162 
#define  F2FS_IOC_COMMIT_ATOMIC_WRITE 161 
#define  F2FS_IOC_DEFRAGMENT 160 
#define  F2FS_IOC_FLUSH_DEVICE 159 
#define  F2FS_IOC_FSGETXATTR 158 
#define  F2FS_IOC_FSSETXATTR 157 
#define  F2FS_IOC_GARBAGE_COLLECT 156 
#define  F2FS_IOC_GARBAGE_COLLECT_RANGE 155 
#define  F2FS_IOC_GETFLAGS 154 
#define  F2FS_IOC_GETVERSION 153 
#define  F2FS_IOC_GET_ENCRYPTION_POLICY 152 
#define  F2FS_IOC_GET_ENCRYPTION_PWSALT 151 
#define  F2FS_IOC_GET_FEATURES 150 
#define  F2FS_IOC_GET_PIN_FILE 149 
#define  F2FS_IOC_GET_VOLUME_NAME 148 
#define  F2FS_IOC_MOVE_RANGE 147 
#define  F2FS_IOC_PRECACHE_EXTENTS 146 
#define  F2FS_IOC_RELEASE_VOLATILE_WRITE 145 
#define  F2FS_IOC_RESIZE_FS 144 
#define  F2FS_IOC_SETFLAGS 143 
#define  F2FS_IOC_SET_ENCRYPTION_POLICY 142 
#define  F2FS_IOC_SET_PIN_FILE 141 
#define  F2FS_IOC_SET_VOLUME_NAME 140 
#define  F2FS_IOC_SHUTDOWN 139 
#define  F2FS_IOC_START_ATOMIC_WRITE 138 
#define  F2FS_IOC_START_VOLATILE_WRITE 137 
#define  F2FS_IOC_WRITE_CHECKPOINT 136 
 int /*<<< orphan*/  F2FS_I_SB (int /*<<< orphan*/ ) ; 
#define  FITRIM 135 
#define  FS_IOC_ADD_ENCRYPTION_KEY 134 
#define  FS_IOC_ENABLE_VERITY 133 
#define  FS_IOC_GET_ENCRYPTION_KEY_STATUS 132 
#define  FS_IOC_GET_ENCRYPTION_POLICY_EX 131 
#define  FS_IOC_MEASURE_VERITY 130 
#define  FS_IOC_REMOVE_ENCRYPTION_KEY 129 
#define  FS_IOC_REMOVE_ENCRYPTION_KEY_ALL_USERS 128 
 int /*<<< orphan*/  f2fs_cp_error (int /*<<< orphan*/ ) ; 
 long f2fs_get_volume_name (struct file*,unsigned long) ; 
 long f2fs_ioc_abort_volatile_write (struct file*) ; 
 long f2fs_ioc_add_encryption_key (struct file*,unsigned long) ; 
 long f2fs_ioc_commit_atomic_write (struct file*) ; 
 long f2fs_ioc_defragment (struct file*,unsigned long) ; 
 long f2fs_ioc_enable_verity (struct file*,unsigned long) ; 
 long f2fs_ioc_fitrim (struct file*,unsigned long) ; 
 long f2fs_ioc_flush_device (struct file*,unsigned long) ; 
 long f2fs_ioc_fsgetxattr (struct file*,unsigned long) ; 
 long f2fs_ioc_fssetxattr (struct file*,unsigned long) ; 
 long f2fs_ioc_gc (struct file*,unsigned long) ; 
 long f2fs_ioc_gc_range (struct file*,unsigned long) ; 
 long f2fs_ioc_get_encryption_key_status (struct file*,unsigned long) ; 
 long f2fs_ioc_get_encryption_policy (struct file*,unsigned long) ; 
 long f2fs_ioc_get_encryption_policy_ex (struct file*,unsigned long) ; 
 long f2fs_ioc_get_encryption_pwsalt (struct file*,unsigned long) ; 
 long f2fs_ioc_get_features (struct file*,unsigned long) ; 
 long f2fs_ioc_get_pin_file (struct file*,unsigned long) ; 
 long f2fs_ioc_getflags (struct file*,unsigned long) ; 
 long f2fs_ioc_getversion (struct file*,unsigned long) ; 
 long f2fs_ioc_measure_verity (struct file*,unsigned long) ; 
 long f2fs_ioc_move_range (struct file*,unsigned long) ; 
 long f2fs_ioc_precache_extents (struct file*,unsigned long) ; 
 long f2fs_ioc_release_volatile_write (struct file*) ; 
 long f2fs_ioc_remove_encryption_key (struct file*,unsigned long) ; 
 long f2fs_ioc_remove_encryption_key_all_users (struct file*,unsigned long) ; 
 long f2fs_ioc_resize_fs (struct file*,unsigned long) ; 
 long f2fs_ioc_set_encryption_policy (struct file*,unsigned long) ; 
 long f2fs_ioc_set_pin_file (struct file*,unsigned long) ; 
 long f2fs_ioc_setflags (struct file*,unsigned long) ; 
 long f2fs_ioc_shutdown (struct file*,unsigned long) ; 
 long f2fs_ioc_start_atomic_write (struct file*) ; 
 long f2fs_ioc_start_volatile_write (struct file*) ; 
 long f2fs_ioc_write_checkpoint (struct file*,unsigned long) ; 
 int /*<<< orphan*/  f2fs_is_checkpoint_ready (int /*<<< orphan*/ ) ; 
 long f2fs_set_volume_name (struct file*,unsigned long) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

long f2fs_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	if (unlikely(f2fs_cp_error(F2FS_I_SB(file_inode(filp)))))
		return -EIO;
	if (!f2fs_is_checkpoint_ready(F2FS_I_SB(file_inode(filp))))
		return -ENOSPC;

	switch (cmd) {
	case F2FS_IOC_GETFLAGS:
		return f2fs_ioc_getflags(filp, arg);
	case F2FS_IOC_SETFLAGS:
		return f2fs_ioc_setflags(filp, arg);
	case F2FS_IOC_GETVERSION:
		return f2fs_ioc_getversion(filp, arg);
	case F2FS_IOC_START_ATOMIC_WRITE:
		return f2fs_ioc_start_atomic_write(filp);
	case F2FS_IOC_COMMIT_ATOMIC_WRITE:
		return f2fs_ioc_commit_atomic_write(filp);
	case F2FS_IOC_START_VOLATILE_WRITE:
		return f2fs_ioc_start_volatile_write(filp);
	case F2FS_IOC_RELEASE_VOLATILE_WRITE:
		return f2fs_ioc_release_volatile_write(filp);
	case F2FS_IOC_ABORT_VOLATILE_WRITE:
		return f2fs_ioc_abort_volatile_write(filp);
	case F2FS_IOC_SHUTDOWN:
		return f2fs_ioc_shutdown(filp, arg);
	case FITRIM:
		return f2fs_ioc_fitrim(filp, arg);
	case F2FS_IOC_SET_ENCRYPTION_POLICY:
		return f2fs_ioc_set_encryption_policy(filp, arg);
	case F2FS_IOC_GET_ENCRYPTION_POLICY:
		return f2fs_ioc_get_encryption_policy(filp, arg);
	case F2FS_IOC_GET_ENCRYPTION_PWSALT:
		return f2fs_ioc_get_encryption_pwsalt(filp, arg);
	case FS_IOC_GET_ENCRYPTION_POLICY_EX:
		return f2fs_ioc_get_encryption_policy_ex(filp, arg);
	case FS_IOC_ADD_ENCRYPTION_KEY:
		return f2fs_ioc_add_encryption_key(filp, arg);
	case FS_IOC_REMOVE_ENCRYPTION_KEY:
		return f2fs_ioc_remove_encryption_key(filp, arg);
	case FS_IOC_REMOVE_ENCRYPTION_KEY_ALL_USERS:
		return f2fs_ioc_remove_encryption_key_all_users(filp, arg);
	case FS_IOC_GET_ENCRYPTION_KEY_STATUS:
		return f2fs_ioc_get_encryption_key_status(filp, arg);
	case F2FS_IOC_GARBAGE_COLLECT:
		return f2fs_ioc_gc(filp, arg);
	case F2FS_IOC_GARBAGE_COLLECT_RANGE:
		return f2fs_ioc_gc_range(filp, arg);
	case F2FS_IOC_WRITE_CHECKPOINT:
		return f2fs_ioc_write_checkpoint(filp, arg);
	case F2FS_IOC_DEFRAGMENT:
		return f2fs_ioc_defragment(filp, arg);
	case F2FS_IOC_MOVE_RANGE:
		return f2fs_ioc_move_range(filp, arg);
	case F2FS_IOC_FLUSH_DEVICE:
		return f2fs_ioc_flush_device(filp, arg);
	case F2FS_IOC_GET_FEATURES:
		return f2fs_ioc_get_features(filp, arg);
	case F2FS_IOC_FSGETXATTR:
		return f2fs_ioc_fsgetxattr(filp, arg);
	case F2FS_IOC_FSSETXATTR:
		return f2fs_ioc_fssetxattr(filp, arg);
	case F2FS_IOC_GET_PIN_FILE:
		return f2fs_ioc_get_pin_file(filp, arg);
	case F2FS_IOC_SET_PIN_FILE:
		return f2fs_ioc_set_pin_file(filp, arg);
	case F2FS_IOC_PRECACHE_EXTENTS:
		return f2fs_ioc_precache_extents(filp, arg);
	case F2FS_IOC_RESIZE_FS:
		return f2fs_ioc_resize_fs(filp, arg);
	case FS_IOC_ENABLE_VERITY:
		return f2fs_ioc_enable_verity(filp, arg);
	case FS_IOC_MEASURE_VERITY:
		return f2fs_ioc_measure_verity(filp, arg);
	case F2FS_IOC_GET_VOLUME_NAME:
		return f2fs_get_volume_name(filp, arg);
	case F2FS_IOC_SET_VOLUME_NAME:
		return f2fs_set_volume_name(filp, arg);
	default:
		return -ENOTTY;
	}
}