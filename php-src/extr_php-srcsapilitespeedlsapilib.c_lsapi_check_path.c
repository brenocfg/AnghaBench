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
 scalar_t__ EACCES ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 scalar_t__ EPERM ; 
 int PATH_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 char* memccpy (char*,char const*,char,int) ; 
 int /*<<< orphan*/ * realpath (char const*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int lsapi_check_path(const char *p, char *final, int max_len)
{
    char resolved_path[PATH_MAX+1];
    int len = 0;
    char *end;
    if (*p != '/')
    {
        if (getcwd(final, max_len) == NULL)
            return -1;
        len = strlen(final);
        *(final + len) = '/';
        ++len;
    }
    end = memccpy(&final[len], p, '\0', PATH_MAX - len);
    if (!end)
    {
        errno = EINVAL;
        return -1;
    }
    p = final;
    if (realpath(p, resolved_path) == NULL
        && errno != ENOENT && errno != EACCES)
        return -1;
    if (strncmp(resolved_path, "/etc/", 5) == 0)
    {
        errno = EPERM;
        return -1;
    }
    return 0;
}