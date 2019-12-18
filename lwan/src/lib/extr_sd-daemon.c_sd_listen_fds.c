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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int EINVAL ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int INT_MAX ; 
 int SD_LISTEN_FDS_START ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 char* getenv (char*) ; 
 scalar_t__ getpid () ; 
 int parse_int (char const*,int) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

int sd_listen_fds(int unset_environment) {
        int n, l, r, fd;
        const char *e;

        e = getenv("LISTEN_PID");
        if (!e) {
                r = 0;
                goto finish;
        }

        l = parse_int(e, -1);
        if (l <= 0) {
                r = -EINVAL;
                goto finish;
        }

        /* Is this for us? */
        if (getpid() != (pid_t)l) {
                r = 0;
                goto finish;
        }

        e = getenv("LISTEN_FDS");
        if (!e) {
                r = 0;
                goto finish;
        }

        n = parse_int(e, -1);
        if (!n) {
                r = 0;
                goto finish;
        }

        static_assert(SD_LISTEN_FDS_START < INT_MAX, "");
        if (n < 0 || n > INT_MAX - SD_LISTEN_FDS_START) {
                r = -EINVAL;
                goto finish;
        }

        for (fd = SD_LISTEN_FDS_START; fd < SD_LISTEN_FDS_START + (int)n; fd++) {
                int flags;

                flags = fcntl(fd, F_GETFD);
                if (flags < 0) {
                        r = -errno;
                        goto finish;
                }

                if (flags & FD_CLOEXEC)
                        continue;

                if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) < 0) {
                        r = -errno;
                        goto finish;
                }
        }

        r = n;

finish:
        if (unset_environment) {
                unsetenv("LISTEN_PID");
                unsetenv("LISTEN_FDS");
        }

        return r;
}