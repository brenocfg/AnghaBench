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
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
set_std_files_to_null(bool stdin_only)
{
#if defined(HAVE_DUP) && defined(HAVE_DUP2)
    int fd;
    if ((fd = open("/dev/null", O_RDWR, 0)) != -1)
    {
        dup2(fd, 0);
        if (!stdin_only)
        {
            dup2(fd, 1);
            dup2(fd, 2);
        }
        if (fd > 2)
        {
            close(fd);
        }
    }
#endif
}