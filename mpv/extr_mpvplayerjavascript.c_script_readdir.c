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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  js_State ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_af_dir (void*,int /*<<< orphan*/ *) ; 
 int checkopt (int /*<<< orphan*/ *,int,char*,char const**,char*) ; 
 int /*<<< orphan*/  jctx (int /*<<< orphan*/ *) ; 
 scalar_t__ js_isundefined (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  push_failure (int /*<<< orphan*/ *,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_last_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* talloc_asprintf_append (char*,char*,char const*,char*) ; 
 char* talloc_strdup (void*,char*) ; 

__attribute__((used)) static void script_readdir(js_State *J, void *af)
{
    //                    0      1        2       3
    const char *filters[] = {"all", "files", "dirs", "normal", NULL};
    const char *path = js_isundefined(J, 1) ? "." : js_tostring(J, 1);
    int t = checkopt(J, 2, "normal", filters, "listing filter");

    DIR *dir = opendir(path);
    if (!dir) {
        push_failure(J, "Cannot open dir");
        return;
    }
    add_af_dir(af, dir);
    set_last_error(jctx(J), 0, NULL);
    js_newarray(J);  // the return value
    char *fullpath = talloc_strdup(af, "");
    struct dirent *e;
    int n = 0;
    while ((e = readdir(dir))) {
        char *name = e->d_name;
        if (t) {
            if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
                continue;
            if (fullpath)
                fullpath[0] = '\0';
            fullpath = talloc_asprintf_append(fullpath, "%s/%s", path, name);
            struct stat st;
            if (stat(fullpath, &st))
                continue;
            if (!(((t & 1) && S_ISREG(st.st_mode)) ||
                  ((t & 2) && S_ISDIR(st.st_mode))))
            {
                continue;
            }
        }
        js_pushstring(J, name);
        js_setindex(J, -2, n++);
    }
}