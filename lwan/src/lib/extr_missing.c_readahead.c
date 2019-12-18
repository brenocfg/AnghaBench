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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  POSIX_FADV_WILLNEED ; 
 int /*<<< orphan*/  posix_fadvise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ssize_t readahead(int fd, off_t offset, size_t count)
{
#if defined(HAVE_POSIX_FADVISE)
    return (ssize_t)posix_fadvise(fd, offset, (off_t)count,
                                  POSIX_FADV_WILLNEED);
#else
    (void)fd;
    (void)offset;
    (void)count;

    return 0;
#endif
}