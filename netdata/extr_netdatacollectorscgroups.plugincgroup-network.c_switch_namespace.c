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
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 

int switch_namespace(const char *prefix, pid_t pid) {
    if(!prefix) prefix = "";

#ifdef HAVE_SETNS

    int i;
    for(i = 0; all_ns[i].name ; i++)
        all_ns[i].fd = proc_pid_fd(prefix, all_ns[i].path, pid);

    int root_fd = proc_pid_fd(prefix, "root", pid);
    int cwd_fd  = proc_pid_fd(prefix, "cwd", pid);

    setgroups(0, NULL);

    // 2 passes - found it at nsenter source code
    // this is related CLONE_NEWUSER functionality

    // This code cannot switch user namespace (it can all the other namespaces)
    // Fortunately, we don't need to switch user namespaces.

    int pass;
    for(pass = 0; pass < 2 ;pass++) {
        for(i = 0; all_ns[i].name ; i++) {
            if (all_ns[i].fd != -1 && all_ns[i].status == -1) {
                if(setns(all_ns[i].fd, all_ns[i].nstype) == -1) {
                    if(pass == 1) {
                        all_ns[i].status = 0;
                        error("Cannot switch to %s namespace of pid %d", all_ns[i].name, (int) pid);
                    }
                }
                else
                    all_ns[i].status = 1;
            }
        }
    }

    setgroups(0, NULL);

    if(root_fd != -1) {
        if(fchdir(root_fd) < 0)
            error("Cannot fchdir() to pid %d root directory", (int)pid);

        if(chroot(".") < 0)
            error("Cannot chroot() to pid %d root directory", (int)pid);

        close(root_fd);
    }

    if(cwd_fd != -1) {
        if(fchdir(cwd_fd) < 0)
            error("Cannot fchdir() to pid %d current working directory", (int)pid);

        close(cwd_fd);
    }

    int do_fork = 0;
    for(i = 0; all_ns[i].name ; i++)
        if(all_ns[i].fd != -1) {

            // CLONE_NEWPID requires a fork() to become effective
            if(all_ns[i].nstype == CLONE_NEWPID && all_ns[i].status)
                do_fork = 1;

            close(all_ns[i].fd);
        }

    if(do_fork)
        continue_as_child();

    return 0;

#else

    errno = ENOSYS;
    error("setns() is missing on this system.");
    return 1;

#endif
}