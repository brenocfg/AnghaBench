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
typedef  int /*<<< orphan*/  thread_name ;
typedef  int /*<<< orphan*/  process_name ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ proc_pidpath (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_set_name_np (int /*<<< orphan*/ ,char*) ; 
 int snprintf (char*,int,char*,char*,char const*) ; 
 char* strrchr (char*,char) ; 

void lwan_set_thread_name(const char *name)
{
    char thread_name[16];
    char process_name[PATH_MAX];
    char *tmp;
    int ret;

    if (proc_pidpath(getpid(), process_name, sizeof(process_name)) < 0)
        return;

    tmp = strrchr(process_name, '/');
    if (!tmp)
        return;

    ret = snprintf(thread_name, sizeof(thread_name), "%s %s", tmp + 1, name);
    if (ret < 0)
        return;

    pthread_set_name_np(pthread_self(), thread_name);
}