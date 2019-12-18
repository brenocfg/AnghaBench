#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ pidinfo_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 char* PROC_PATH ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atol (char*) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_debug ; 
 scalar_t__ is_numeric (char*) ; 
 int /*<<< orphan*/  nfprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  nperror (char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int readlink (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,...) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int find_pids_by_binary_name(char *bin_name, pidinfo_t *pid_list, int max_pids)
{
DIR *proc;
struct dirent *direntp;
struct stat stat_buf;
char fullpath_dir[MAXPATHLEN + 1];
char fullpath_exe[MAXPATHLEN + 1];
char exe[MAXPATHLEN + 1];
ssize_t len;
int pid_count=0;

proc=opendir(PROC_PATH);
if (!proc) {
    nperror("opendir");
    nfprintf(stderr,"Can't open %s\n",PROC_PATH);
    exit(EXIT_FAILURE);
}

while ((direntp = readdir(proc)) != NULL) {
    snprintf(fullpath_dir, MAXPATHLEN, "%s/%s", PROC_PATH, direntp->d_name);

    if (stat(fullpath_dir, &stat_buf) == -1) {
        if (flag_debug)
            nperror("stat (find_pids_by_binary_name)");
        continue;
    }

    if ((S_ISDIR(stat_buf.st_mode) && is_numeric(direntp->d_name))) {
        snprintf(fullpath_exe, MAXPATHLEN, "%s/exe", fullpath_dir);
        len=readlink(fullpath_exe, exe, MAXPATHLEN);
        if (len != -1)
            exe[len] = 0;
        else {
            // Will be mostly "Permission denied"
            //~ nperror("readlink");
            continue;
        }

        if (!strcmp(basename(exe), bin_name)) {
            pid_list[pid_count].pid = atol(direntp->d_name);
            strcpy(pid_list[pid_count].name, bin_name);
            pid_count++;
            if(pid_count == max_pids)
                break;
        }
    }
}

closedir(proc);
return pid_count;
}