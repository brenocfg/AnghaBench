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
struct stat {unsigned int const st_mode; unsigned int const st_size; unsigned int const st_atime; unsigned int const st_mtime; unsigned int const st_ctime; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (unsigned int const) ; 
 int /*<<< orphan*/  S_ISREG (unsigned int const) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,unsigned int const) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static int script_file_info(lua_State *L)
{
    const char *path = luaL_checkstring(L, 1);

    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        lua_pushnil(L);
        lua_pushstring(L, "error");
        return 2;
    }

    lua_newtable(L); // Result stat table

    const char * stat_names[] = {
        "mode", "size",
        "atime", "mtime", "ctime", NULL
    };
    const unsigned int stat_values[] = {
        statbuf.st_mode,
        statbuf.st_size,
        statbuf.st_atime,
        statbuf.st_mtime,
        statbuf.st_ctime
    };

    // Add all fields
    for (int i = 0; stat_names[i]; i++) {
        lua_pushinteger(L, stat_values[i]);
        lua_setfield(L, -2, stat_names[i]);
    }

    // Convenience booleans
    lua_pushboolean(L, S_ISREG(statbuf.st_mode));
    lua_setfield(L, -2, "is_file");

    lua_pushboolean(L, S_ISDIR(statbuf.st_mode));
    lua_setfield(L, -2, "is_dir");

    // Return table
    return 1;
}