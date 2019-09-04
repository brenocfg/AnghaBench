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
 long ENOTTY ; 
#define  F2FS_IOC_ABORT_VOLATILE_WRITE 152 
#define  F2FS_IOC_COMMIT_ATOMIC_WRITE 151 
#define  F2FS_IOC_DEFRAGMENT 150 
#define  F2FS_IOC_FLUSH_DEVICE 149 
#define  F2FS_IOC_FSGETXATTR 148 
#define  F2FS_IOC_FSSETXATTR 147 
#define  F2FS_IOC_GARBAGE_COLLECT 146 
#define  F2FS_IOC_GARBAGE_COLLECT_RANGE 145 
#define  F2FS_IOC_GETFLAGS 144 
#define  F2FS_IOC_GETVERSION 143 
#define  F2FS_IOC_GET_ENCRYPTION_POLICY 142 
#define  F2FS_IOC_GET_ENCRYPTION_PWSALT 141 
#define  F2FS_IOC_GET_FEATURES 140 
#define  F2FS_IOC_GET_PIN_FILE 139 
#define  F2FS_IOC_MOVE_RANGE 138 
#define  F2FS_IOC_PRECACHE_EXTENTS 137 
#define  F2FS_IOC_RELEASE_VOLATILE_WRITE 136 
#define  F2FS_IOC_SETFLAGS 135 
#define  F2FS_IOC_SET_ENCRYPTION_POLICY 134 
#define  F2FS_IOC_SET_PIN_FILE 133 
#define  F2FS_IOC_SHUTDOWN 132 
#define  F2FS_IOC_START_ATOMIC_WRITE 131 
#define  F2FS_IOC_START_VOLATILE_WRITE 130 
#define  F2FS_IOC_WRITE_CHECKPOINT 129 
 int /*<<< orphan*/  F2FS_I_SB (int /*<<< orphan*/ ) ; 
#define  FITRIM 128 
 int /*<<< orphan*/  f2fs_cp_error (int /*<<< orphan*/ ) ; 
 long f2fs_ioc_abort_volatile_write (struct file*) ; 
 long f2fs_ioc_commit_atomic_write (struct file*) ; 
 long f2fs_ioc_defragment (struct file*,unsigned long) ; 
 long f2fs_ioc_fitrim (struct file*,unsigned long) ; 
 long f2fs_ioc_flush_device (struct file*,unsigned long) ; 
 long f2fs_ioc_fsgetxattr (struct file*,unsigned long) ; 
 long f2fs_ioc_fssetxattr (struct file*,unsigned long) ; 
 long f2fs_ioc_gc (struct file*,unsigned long) ; 
 long f2fs_ioc_gc_range (struct file*,unsigned long) ; 
 long f2fs_ioc_get_encryption_policy (struct file*,unsigned long) ; 
 long f2fs_ioc_get_encryption_pwsalt (struct file*,unsigned long) ; 
 long f2fs_ioc_get_features (struct file*,unsigned long) ; 
 long f2fs_ioc_get_pin_file (struct file*,unsigned long) ; 
 long f2fs_ioc_getflags (struct file*,unsigned long) ; 
 long f2fs_ioc_getversion (struct file*,unsigned long) ; 
 long f2fs_ioc_move_range (struct file*,unsigned long) ; 
 long f2fs_ioc_precache_extents (struct file*,unsigned long) ; 
 long f2fs_ioc_release_volatile_write (struct file*) ; 
 long f2fs_ioc_set_encryption_policy (struct file*,unsigned long) ; 
 long f2fs_ioc_set_pin_file (struct file*,unsigned long) ; 
 long f2fs_ioc_setflags (struct file*,unsigned long) ; 
 long f2fs_ioc_shutdown (struct file*,unsigned long) ; 
 long f2fs_ioc_start_atomic_write (struct file*) ; 
 long f2fs_ioc_start_volatile_write (struct file*) ; 
 long f2fs_ioc_write_checkpoint (struct file*,unsigned long) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

long f2fs_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	if (unlikely(f2fs_cp_error(F2FS_I_SB(file_inode(filp)))))
		return -EIO;

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
	default:
		return -ENOTTY;
	}
}