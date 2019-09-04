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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_SYSTEM ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 scalar_t__ become_user (char const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  create_needed_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 scalar_t__ ftruncate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getgid () ; 
 int getpid () ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  netdata_configured_cache_dir ; 
 int /*<<< orphan*/  netdata_configured_varlib_dir ; 
 int /*<<< orphan*/  oom_score_adj () ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char const* pidfile ; 
 int /*<<< orphan*/  sched_setscheduler_set () ; 
 scalar_t__ setsid () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  umask (int) ; 
 scalar_t__ write (int,char*,int /*<<< orphan*/ ) ; 

int become_daemon(int dont_fork, const char *user)
{
    if(!dont_fork) {
        int i = fork();
        if(i == -1) {
            perror("cannot fork");
            exit(1);
        }
        if(i != 0) {
            exit(0); // the parent
        }

        // become session leader
        if (setsid() < 0) {
            perror("Cannot become session leader.");
            exit(2);
        }

        // fork() again
        i = fork();
        if(i == -1) {
            perror("cannot fork");
            exit(1);
        }
        if(i != 0) {
            exit(0); // the parent
        }
    }

    // generate our pid file
    int pidfd = -1;
    if(pidfile[0]) {
        pidfd = open(pidfile, O_WRONLY | O_CREAT, 0644);
        if(pidfd >= 0) {
            if(ftruncate(pidfd, 0) != 0)
                error("Cannot truncate pidfile '%s'.", pidfile);

            char b[100];
            sprintf(b, "%d\n", getpid());
            ssize_t i = write(pidfd, b, strlen(b));
            if(i <= 0)
                error("Cannot write pidfile '%s'.", pidfile);
        }
        else error("Failed to open pidfile '%s'.", pidfile);
    }

    // Set new file permissions
    umask(0007);

    // adjust my Out-Of-Memory score
    oom_score_adj();

    // never become a problem
    sched_setscheduler_set();

    if(user && *user) {
        if(become_user(user, pidfd) != 0) {
            error("Cannot become user '%s'. Continuing as we are.", user);
        }
        else debug(D_SYSTEM, "Successfully became user '%s'.", user);
    }
    else {
        create_needed_dir(netdata_configured_cache_dir, getuid(), getgid());
        create_needed_dir(netdata_configured_varlib_dir, getuid(), getgid());
    }

    if(pidfd != -1)
        close(pidfd);

    return(0);
}