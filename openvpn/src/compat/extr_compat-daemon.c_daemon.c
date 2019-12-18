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
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setsid () ; 

int
daemon(int nochdir, int noclose)
{
#if defined(HAVE_FORK) && defined(HAVE_SETSID)
    switch (fork())
    {
        case -1:
            return (-1);

        case 0:
            break;

        default:
            exit(0);
    }

    if (setsid() == -1)
    {
        return (-1);
    }

    if (!nochdir)
    {
        chdir("/");
    }

    if (!noclose)
    {
#if defined(HAVE_DUP) && defined(HAVE_DUP2)
        int fd;
        if ((fd = open("/dev/null", O_RDWR, 0)) != -1)
        {
            dup2(fd, 0);
            dup2(fd, 1);
            dup2(fd, 2);
            if (fd > 2)
            {
                close(fd);
            }
        }
#endif
    }

    return 0;
#else  /* if defined(HAVE_FORK) && defined(HAVE_SETSID) */
    (void)nochdir;
    (void)noclose;
    errno = EFAULT;
    return -1;
#endif /* if defined(HAVE_FORK) && defined(HAVE_SETSID) */
}