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
struct file {TYPE_1__* f_op; } ;
struct TYPE_2__ {long (* unlocked_ioctl ) (struct file*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 long ENOTTY ; 
#define  FITRIM 132 
#define  FS_IOC_GETFLAGS 131 
#define  FS_IOC_GETVERSION 130 
#define  FS_IOC_SETFLAGS 129 
#define  FS_IOC_SETVERSION 128 
 struct file* ecryptfs_file_to_lower (struct file*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  fsstack_copy_attr_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long stub1 (struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long
ecryptfs_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct file *lower_file = ecryptfs_file_to_lower(file);
	long rc = -ENOTTY;

	if (!lower_file->f_op->unlocked_ioctl)
		return rc;

	switch (cmd) {
	case FITRIM:
	case FS_IOC_GETFLAGS:
	case FS_IOC_SETFLAGS:
	case FS_IOC_GETVERSION:
	case FS_IOC_SETVERSION:
		rc = lower_file->f_op->unlocked_ioctl(lower_file, cmd, arg);
		fsstack_copy_attr_all(file_inode(file), file_inode(lower_file));

		return rc;
	default:
		return rc;
	}
}