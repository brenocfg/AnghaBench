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
 int /*<<< orphan*/  AT_FDCWD ; 
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  SYS_renameat2 ; 
 int errno ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,unsigned int) ; 

int rename2_file(char *from, char *to, unsigned int flags)
{
	int err;

#ifndef SYS_renameat2
#  ifdef __x86_64__
#    define SYS_renameat2 316
#  endif
#  ifdef __i386__
#    define SYS_renameat2 353
#  endif
#endif

#ifdef SYS_renameat2
	err = syscall(SYS_renameat2, AT_FDCWD, from, AT_FDCWD, to, flags);
	if (err < 0) {
		if (errno != ENOSYS)
			return -errno;
		else
			return -EINVAL;
	}
	return 0;
#else
	return -EINVAL;
#endif
}