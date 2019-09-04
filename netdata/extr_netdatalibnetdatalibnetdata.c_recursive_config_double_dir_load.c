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
 scalar_t__ DT_LNK ; 
 scalar_t__ DT_REG ; 
 scalar_t__ DT_UNKNOWN ; 
 int /*<<< orphan*/  D_HEALTH ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  error (char*,char const*,...) ; 
 int /*<<< orphan*/  freez (char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 scalar_t__ path_is_dir (char*,char*) ; 
 scalar_t__ path_is_file (char*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdupz_path_subpath (char const*,char const*) ; 
 size_t strlen (char*) ; 

void recursive_config_double_dir_load(const char *user_path, const char *stock_path, const char *subpath, int (*callback)(const char *filename, void *data), void *data, size_t depth) {
    if(depth > 3) {
        error("CONFIG: Max directory depth reached while reading user path '%s', stock path '%s', subpath '%s'", user_path, stock_path, subpath);
        return;
    }

    char *udir = strdupz_path_subpath(user_path, subpath);
    char *sdir = strdupz_path_subpath(stock_path, subpath);

    debug(D_HEALTH, "CONFIG traversing user-config directory '%s', stock config directory '%s'", udir, sdir);

    DIR *dir = opendir(udir);
    if (!dir) {
        error("CONFIG cannot open user-config directory '%s'.", udir);
    }
    else {
        struct dirent *de = NULL;
        while((de = readdir(dir))) {
            if(de->d_type == DT_DIR || de->d_type == DT_LNK) {
                if( !de->d_name[0] ||
                    (de->d_name[0] == '.' && de->d_name[1] == '\0') ||
                    (de->d_name[0] == '.' && de->d_name[1] == '.' && de->d_name[2] == '\0')
                        ) {
                    debug(D_HEALTH, "CONFIG ignoring user-config directory '%s/%s'", udir, de->d_name);
                    continue;
                }

                if(path_is_dir(udir, de->d_name)) {
                    recursive_config_double_dir_load(udir, sdir, de->d_name, callback, data, depth + 1);
                    continue;
                }
            }

            if(de->d_type == DT_UNKNOWN || de->d_type == DT_REG || de->d_type == DT_LNK) {
                size_t len = strlen(de->d_name);
                if(path_is_file(udir, de->d_name) &&
                   len > 5 && !strcmp(&de->d_name[len - 5], ".conf")) {
                    char *filename = strdupz_path_subpath(udir, de->d_name);
                    debug(D_HEALTH, "CONFIG calling callback for user file '%s'", filename);
                    callback(filename, data);
                    freez(filename);
                    continue;
                }
            }

            debug(D_HEALTH, "CONFIG ignoring user-config file '%s/%s' of type %d", udir, de->d_name, (int)de->d_type);
        }

        closedir(dir);
    }

    debug(D_HEALTH, "CONFIG traversing stock config directory '%s', user config directory '%s'", sdir, udir);

    dir = opendir(sdir);
    if (!dir) {
        error("CONFIG cannot open stock config directory '%s'.", sdir);
    }
    else {
        struct dirent *de = NULL;
        while((de = readdir(dir))) {
            if(de->d_type == DT_DIR || de->d_type == DT_LNK) {
                if( !de->d_name[0] ||
                    (de->d_name[0] == '.' && de->d_name[1] == '\0') ||
                    (de->d_name[0] == '.' && de->d_name[1] == '.' && de->d_name[2] == '\0')
                        ) {
                    debug(D_HEALTH, "CONFIG ignoring stock config directory '%s/%s'", sdir, de->d_name);
                    continue;
                }

                if(path_is_dir(sdir, de->d_name)) {
                    // we recurse in stock subdirectory, only when there is no corresponding
                    // user subdirectory - to avoid reading the files twice

                    if(!path_is_dir(udir, de->d_name))
                        recursive_config_double_dir_load(udir, sdir, de->d_name, callback, data, depth + 1);

                    continue;
                }
            }

            if(de->d_type == DT_UNKNOWN || de->d_type == DT_REG || de->d_type == DT_LNK) {
                size_t len = strlen(de->d_name);
                if(path_is_file(sdir, de->d_name) && !path_is_file(udir, de->d_name) &&
                   len > 5 && !strcmp(&de->d_name[len - 5], ".conf")) {
                    char *filename = strdupz_path_subpath(sdir, de->d_name);
                    debug(D_HEALTH, "CONFIG calling callback for stock file '%s'", filename);
                    callback(filename, data);
                    freez(filename);
                    continue;
                }

            }

            debug(D_HEALTH, "CONFIG ignoring stock-config file '%s/%s' of type %d", udir, de->d_name, (int)de->d_type);
        }

        closedir(dir);
    }

    debug(D_HEALTH, "CONFIG done traversing user-config directory '%s', stock config directory '%s'", udir, sdir);

    freez(udir);
    freez(sdir);
}