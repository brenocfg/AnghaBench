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

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 scalar_t__ read_pid_from_cgroup_file (char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,char const*) ; 

pid_t read_pid_from_cgroup_files(const char *path) {
    char filename[FILENAME_MAX + 1];

    snprintfz(filename, FILENAME_MAX, "%s/cgroup.procs", path);
    pid_t pid = read_pid_from_cgroup_file(filename);
    if(pid > 0) return pid;

    snprintfz(filename, FILENAME_MAX, "%s/tasks", path);
    return read_pid_from_cgroup_file(filename);
}