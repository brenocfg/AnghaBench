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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (void*,char**,int,char*) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compare_filename ; 
 char* mp_path_join (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  qsort (char**,int,int,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 

__attribute__((used)) static char **list_script_files(void *talloc_ctx, char *path)
{
    char **files = NULL;
    int count = 0;
    DIR *dp = opendir(path);
    if (!dp)
        return NULL;
    struct dirent *ep;
    while ((ep = readdir(dp))) {
        char *fname = mp_path_join(talloc_ctx, path, ep->d_name);
        struct stat s;
        if (!stat(fname, &s) && S_ISREG(s.st_mode))
            MP_TARRAY_APPEND(talloc_ctx, files, count, fname);
    }
    closedir(dp);
    if (files)
        qsort(files, count, sizeof(char *), compare_filename);
    MP_TARRAY_APPEND(talloc_ctx, files, count, NULL);
    return files;
}