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
struct fuse_file {int /*<<< orphan*/  fc; } ;
struct file {struct fuse_file* private_data; } ;
struct cuse_conn {scalar_t__ unrestricted_ioctl; } ;

/* Variables and functions */
 unsigned int FUSE_IOCTL_COMPAT ; 
 unsigned int FUSE_IOCTL_UNRESTRICTED ; 
 struct cuse_conn* fc_to_cc (int /*<<< orphan*/ ) ; 
 long fuse_do_ioctl (struct file*,unsigned int,unsigned long,unsigned int) ; 

__attribute__((used)) static long cuse_file_compat_ioctl(struct file *file, unsigned int cmd,
				   unsigned long arg)
{
	struct fuse_file *ff = file->private_data;
	struct cuse_conn *cc = fc_to_cc(ff->fc);
	unsigned int flags = FUSE_IOCTL_COMPAT;

	if (cc->unrestricted_ioctl)
		flags |= FUSE_IOCTL_UNRESTRICTED;

	return fuse_do_ioctl(file, cmd, arg, flags);
}