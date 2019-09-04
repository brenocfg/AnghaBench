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
struct fuse_conn {int minor; } ;
struct file {TYPE_1__* f_mapping; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 long ENOTTY ; 
 int FUSE_IOCTL_COMPAT ; 
 int FUSE_IOCTL_DIR ; 
 long fuse_ioctl_common (struct file*,unsigned int,unsigned long,int) ; 
 struct fuse_conn* get_fuse_conn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long fuse_dir_compat_ioctl(struct file *file, unsigned int cmd,
				   unsigned long arg)
{
	struct fuse_conn *fc = get_fuse_conn(file->f_mapping->host);

	if (fc->minor < 18)
		return -ENOTTY;

	return fuse_ioctl_common(file, cmd, arg,
				 FUSE_IOCTL_COMPAT | FUSE_IOCTL_DIR);
}