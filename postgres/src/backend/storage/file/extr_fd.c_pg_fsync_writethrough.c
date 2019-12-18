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
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  F_FULLFSYNC ; 
 int _commit (int) ; 
 scalar_t__ enableFsync ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pg_fsync_writethrough(int fd)
{
	if (enableFsync)
	{
#ifdef WIN32
		return _commit(fd);
#elif defined(F_FULLFSYNC)
		return (fcntl(fd, F_FULLFSYNC, 0) == -1) ? -1 : 0;
#else
		errno = ENOSYS;
		return -1;
#endif
	}
	else
		return 0;
}