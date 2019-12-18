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
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dup (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 char* get_env (char*,char const**) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
daemonize(const char *envp[])
{
    const char *daemon_string = get_env("daemon", envp);
    if (daemon_string && daemon_string[0] == '1')
    {
        const char *log_redirect = get_env("daemon_log_redirect", envp);
        int fd = -1;
        if (log_redirect && log_redirect[0] == '1')
        {
            fd = dup(2);
        }
        if (daemon(0, 0) < 0)
        {
            warn("DOWN-ROOT: daemonization failed");
        }
        else if (fd >= 3)
        {
            dup2(fd, 2);
            close(fd);
        }
    }
}