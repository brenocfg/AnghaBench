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
struct dirent {scalar_t__ d_type; char* d_name; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 scalar_t__ read_pid_from_cgroup_files (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,char const*,char*) ; 

pid_t read_pid_from_cgroup(const char *path) {
    pid_t pid = read_pid_from_cgroup_files(path);
    if (pid > 0) return pid;

    DIR *dir = opendir(path);
    if (!dir) {
        error("cannot read directory '%s'", path);
        return 0;
    }

    struct dirent *de = NULL;
    while ((de = readdir(dir))) {
        if (de->d_type == DT_DIR
            && (
                    (de->d_name[0] == '.' && de->d_name[1] == '\0')
                    || (de->d_name[0] == '.' && de->d_name[1] == '.' && de->d_name[2] == '\0')
            ))
            continue;

        if (de->d_type == DT_DIR) {
            char filename[FILENAME_MAX + 1];
            snprintfz(filename, FILENAME_MAX, "%s/%s", path, de->d_name);
            pid = read_pid_from_cgroup(filename);
            if(pid > 0) break;
        }
    }
    closedir(dir);
    return pid;
}