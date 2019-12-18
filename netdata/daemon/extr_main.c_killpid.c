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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_EXIT ; 
#define  EPERM 129 
#define  ESRCH 128 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int killpid(pid_t pid) {
    int ret;
    debug(D_EXIT, "Request to kill pid %d", pid);

    errno = 0;
    ret = kill(pid, SIGTERM);
    if (ret == -1) {
        switch(errno) {
            case ESRCH:
                // We wanted the process to exit so just let the caller handle.
                return ret;

            case EPERM:
                error("Cannot kill pid %d, but I do not have enough permissions.", pid);
                break;

            default:
                error("Cannot kill pid %d, but I received an error.", pid);
                break;
        }
    }

    return ret;
}