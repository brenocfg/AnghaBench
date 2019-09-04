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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int luaL_checkoption (int /*<<< orphan*/ *,int,char*,char const**) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* talloc_asprintf_append (char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static int script_readdir(lua_State *L)
{
    //                    0      1        2       3
    const char *fmts[] = {"all", "files", "dirs", "normal", NULL};
    const char *path = luaL_checkstring(L, 1);
    int t = luaL_checkoption(L, 2, "normal", fmts);
    DIR *dir = opendir(path);
    if (!dir) {
        lua_pushnil(L);
        lua_pushstring(L, "error");
        return 2;
    }
    lua_newtable(L); // list
    char *fullpath = NULL;
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
                continue;
        }
        lua_pushinteger(L, ++n); // list index
        lua_pushstring(L, name); // list index name
        lua_settable(L, -3); // list
    }
    closedir(dir);
    talloc_free(fullpath);
    return 1;
}