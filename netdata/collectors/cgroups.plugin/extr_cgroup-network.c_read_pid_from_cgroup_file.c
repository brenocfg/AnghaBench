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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  info (char*,scalar_t__,char const*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfile_open_flags ; 

pid_t read_pid_from_cgroup_file(const char *filename) {
    int fd = open(filename, procfile_open_flags);
    if(fd == -1) {
        error("Cannot open pid_from_cgroup() file '%s'.", filename);
        return 0;
    }

    FILE *fp = fdopen(fd, "r");
    if(!fp) {
        error("Cannot upgrade fd to fp for file '%s'.", filename);
        return 0;
    }

    char buffer[100 + 1];
    pid_t pid = 0;
    char *s;
    while((s = fgets(buffer, 100, fp))) {
        buffer[100] = '\0';
        pid = atoi(s);
        if(pid > 0) break;
    }

    fclose(fp);

#ifdef NETDATA_INTERNAL_CHECKS
    if(pid > 0) info("found pid %d on file '%s'", pid, filename);
#endif

    return pid;
}