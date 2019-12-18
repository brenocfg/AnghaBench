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
 int /*<<< orphan*/  D_CGROUP ; 
 int FILENAME_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int config_get_boolean (char*,char*,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  enabled_cgroup_paths ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  freez (char*) ; 
 char* mallocz (size_t) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int simple_pattern_matches (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static inline int find_dir_in_subdirs(const char *base, const char *this, void (*callback)(const char *)) {
    if(!this) this = base;
    debug(D_CGROUP, "searching for directories in '%s' (base '%s')", this?this:"", base);

    size_t dirlen = strlen(this), baselen = strlen(base);

    int ret = -1;
    int enabled = -1;

    const char *relative_path = &this[baselen];
    if(!*relative_path) relative_path = "/";

    DIR *dir = opendir(this);
    if(!dir) {
        error("CGROUP: cannot read directory '%s'", base);
        return ret;
    }
    ret = 1;

    callback(relative_path);

    struct dirent *de = NULL;
    while((de = readdir(dir))) {
        if(de->d_type == DT_DIR
            && (
                (de->d_name[0] == '.' && de->d_name[1] == '\0')
                || (de->d_name[0] == '.' && de->d_name[1] == '.' && de->d_name[2] == '\0')
                ))
            continue;

        if(de->d_type == DT_DIR) {
            if(enabled == -1) {
                const char *r = relative_path;
                if(*r == '\0') r = "/";

                // do not decent in directories we are not interested
                int def = simple_pattern_matches(enabled_cgroup_paths, r);

                // we check for this option here
                // so that the config will not have settings
                // for leaf directories
                char option[FILENAME_MAX + 1];
                snprintfz(option, FILENAME_MAX, "search for cgroups under %s", r);
                option[FILENAME_MAX] = '\0';
                enabled = config_get_boolean("plugin:cgroups", option, def);
            }

            if(enabled) {
                char *s = mallocz(dirlen + strlen(de->d_name) + 2);
                strcpy(s, this);
                strcat(s, "/");
                strcat(s, de->d_name);
                int ret2 = find_dir_in_subdirs(base, s, callback);
                if(ret2 > 0) ret += ret2;
                freez(s);
            }
        }
    }

    closedir(dir);
    return ret;
}