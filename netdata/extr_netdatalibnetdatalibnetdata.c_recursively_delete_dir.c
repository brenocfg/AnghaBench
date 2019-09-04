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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,char const*,...) ; 
 int /*<<< orphan*/  info (char*,char const*,...) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int rmdir (char const*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,char const*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int unlink (char*) ; 

int recursively_delete_dir(const char *path, const char *reason) {
    DIR *dir = opendir(path);
    if(!dir) {
        error("Cannot read %s directory to be deleted '%s'", reason?reason:"", path);
        return -1;
    }

    int ret = 0;
    struct dirent *de = NULL;
    while((de = readdir(dir))) {
        if(de->d_type == DT_DIR
           && (
                   (de->d_name[0] == '.' && de->d_name[1] == '\0')
                   || (de->d_name[0] == '.' && de->d_name[1] == '.' && de->d_name[2] == '\0')
           ))
            continue;

        char fullpath[FILENAME_MAX + 1];
        snprintfz(fullpath, FILENAME_MAX, "%s/%s", path, de->d_name);

        if(de->d_type == DT_DIR) {
            int r = recursively_delete_dir(fullpath, reason);
            if(r > 0) ret += r;
            continue;
        }

        info("Deleting %s file '%s'", reason?reason:"", fullpath);
        if(unlikely(unlink(fullpath) == -1))
            error("Cannot delete %s file '%s'", reason?reason:"", fullpath);
        else
            ret++;
    }

    info("Deleting empty directory '%s'", path);
    if(unlikely(rmdir(path) == -1))
        error("Cannot delete empty directory '%s'", path);
    else
        ret++;

    closedir(dir);

    return ret;
}