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
struct stat {double const st_mode; double const st_size; double const st_atime; double const st_mtime; double const st_ctime; } ;
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (double const) ; 
 int /*<<< orphan*/  S_ISREG (double const) ; 
 int /*<<< orphan*/  jctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_setproperty (int /*<<< orphan*/ *,int,char*) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  push_failure (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  push_nums_obj (int /*<<< orphan*/ *,char const**,double const*) ; 
 int /*<<< orphan*/  set_last_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static void script_file_info(js_State *J)
{
    const char *path = js_tostring(J, 1);

    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        push_failure(J, "Cannot stat path");
        return;
    }
    // Clear last error
    set_last_error(jctx(J), 0, NULL);

    const char * stat_names[] = {
        "mode", "size",
        "atime", "mtime", "ctime", NULL
    };
    const double stat_values[] = {
        statbuf.st_mode,
        statbuf.st_size,
        statbuf.st_atime,
        statbuf.st_mtime,
        statbuf.st_ctime
    };
    // Create an object and add all fields
    push_nums_obj(J, stat_names, stat_values);

    // Convenience booleans
    js_pushboolean(J, S_ISREG(statbuf.st_mode));
    js_setproperty(J, -2, "is_file");

    js_pushboolean(J, S_ISDIR(statbuf.st_mode));
    js_setproperty(J, -2, "is_dir");
}