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
 int PATH_MAX ; 
 int lsapi_check_path (char const*,char*,int) ; 
 int lsapi_reopen_stderr2 (char*) ; 
 scalar_t__ s_uid ; 

__attribute__((used)) static int lsapi_reopen_stderr(const char *p)
{
    char full_path[PATH_MAX];
    if (s_uid == 0)
        return -1;
    if (lsapi_check_path(p, full_path, PATH_MAX) == -1)
    {
        LSAPI_perror_r(NULL, "Invalid custom stderr log path", p);
        return -1;
    }
    return lsapi_reopen_stderr2(full_path);
}