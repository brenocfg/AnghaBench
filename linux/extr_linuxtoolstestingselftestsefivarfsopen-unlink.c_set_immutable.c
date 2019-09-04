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

/* Variables and functions */
 unsigned int FS_IMMUTABLE_FL ; 
 int /*<<< orphan*/  FS_IOC_GETFLAGS ; 
 int /*<<< orphan*/  FS_IOC_SETFLAGS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int ioctl (int,int /*<<< orphan*/ ,unsigned int*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_immutable(const char *path, int immutable)
{
	unsigned int flags;
	int fd;
	int rc;
	int error;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return fd;

	rc = ioctl(fd, FS_IOC_GETFLAGS, &flags);
	if (rc < 0) {
		error = errno;
		close(fd);
		errno = error;
		return rc;
	}

	if (immutable)
		flags |= FS_IMMUTABLE_FL;
	else
		flags &= ~FS_IMMUTABLE_FL;

	rc = ioctl(fd, FS_IOC_SETFLAGS, &flags);
	error = errno;
	close(fd);
	errno = error;
	return rc;
}