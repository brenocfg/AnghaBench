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
 int /*<<< orphan*/  LSAPI_perror_r (int /*<<< orphan*/ *,char*,char const*) ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  free (char const*) ; 
 int open (char const*,int,int) ; 
 char const* s_stderr_log_path ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int lsapi_reopen_stderr2(const char *full_path)
{
    int newfd = open(full_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (newfd == -1)
    {
        LSAPI_perror_r(NULL, "Failed to open custom stderr log", full_path);
        return -1;
    }
    if (newfd != 2)
    {
        dup2(newfd, 2);
        close(newfd);
        dup2(2, 1);
    }
    if (s_stderr_log_path && full_path != s_stderr_log_path)
    {
        free(s_stderr_log_path);
        s_stderr_log_path = NULL;
    }
    s_stderr_log_path = strdup(full_path);
    return 0;
}