#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  global; } ;

/* Variables and functions */
 TYPE_1__* get_mpctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 char** mp_find_all_config_files (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_path_join (void*,char*,char*) ; 
 char* talloc_asprintf_append (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 
 char* talloc_strdup (void*,char const*) ; 

__attribute__((used)) static void set_path(lua_State *L)
{
    void *tmp = talloc_new(NULL);

    lua_getglobal(L, "package"); // package
    lua_getfield(L, -1, "path"); // package path
    const char *path = lua_tostring(L, -1);

    char *newpath = talloc_strdup(tmp, path ? path : "");
    char **luadir = mp_find_all_config_files(tmp, get_mpctx(L)->global, "scripts");
    for (int i = 0; luadir && luadir[i]; i++) {
        newpath = talloc_asprintf_append(newpath, ";%s",
                        mp_path_join(tmp, luadir[i], "?.lua"));
    }

    lua_pushstring(L, newpath);  // package path newpath
    lua_setfield(L, -3, "path"); // package path
    lua_pop(L, 2);  // -

    talloc_free(tmp);
}