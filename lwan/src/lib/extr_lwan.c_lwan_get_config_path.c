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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ proc_pidpath (int /*<<< orphan*/ ,char*,int) ; 
 int snprintf (char*,size_t,char*,char*) ; 
 char* strrchr (char*,char) ; 

const char *lwan_get_config_path(char *path_buf, size_t path_buf_len)
{
    char buffer[PATH_MAX];

    if (proc_pidpath(getpid(), buffer, sizeof(buffer)) < 0)
        goto out;

    char *path = strrchr(buffer, '/');
    if (!path)
        goto out;
    int ret = snprintf(path_buf, path_buf_len, "%s.conf", path + 1);
    if (ret < 0 || ret >= (int)path_buf_len)
        goto out;

    return path_buf;

out:
    return "lwan.conf";
}