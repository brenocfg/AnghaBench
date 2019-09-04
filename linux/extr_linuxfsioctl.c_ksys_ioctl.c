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
struct fd {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int EBADF ; 
 int do_vfs_ioctl (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned long) ; 
 struct fd fdget (unsigned int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int security_file_ioctl (int /*<<< orphan*/ ,unsigned int,unsigned long) ; 

int ksys_ioctl(unsigned int fd, unsigned int cmd, unsigned long arg)
{
	int error;
	struct fd f = fdget(fd);

	if (!f.file)
		return -EBADF;
	error = security_file_ioctl(f.file, cmd, arg);
	if (!error)
		error = do_vfs_ioctl(f.file, fd, cmd, arg);
	fdput(f);
	return error;
}