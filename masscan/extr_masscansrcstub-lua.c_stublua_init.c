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

/* Variables and functions */
 int /*<<< orphan*/  RTLD_LAZY ; 
 void* dlopen (char const*,int /*<<< orphan*/ ) ; 
 void* dlsym (void*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * luaL_checkinteger ; 
 int /*<<< orphan*/ * luaL_checklstring ; 
 int /*<<< orphan*/ * luaL_checkudata ; 
 int /*<<< orphan*/ * luaL_len ; 
 int /*<<< orphan*/ * luaL_loadbufferx ; 
 int /*<<< orphan*/ * luaL_loadfilex ; 
 int /*<<< orphan*/ * luaL_loadstring ; 
 int /*<<< orphan*/ * luaL_newmetatable ; 
 int /*<<< orphan*/ * luaL_newstate ; 
 int /*<<< orphan*/ * luaL_openlibs ; 
 int /*<<< orphan*/ * luaL_ref ; 
 int /*<<< orphan*/ * luaL_setfuncs ; 
 int /*<<< orphan*/ * luaL_setmetatable ; 
 int /*<<< orphan*/ * luaL_unref ; 
 int /*<<< orphan*/ * lua_close ; 
 int /*<<< orphan*/ * lua_getfield ; 
 int /*<<< orphan*/ * lua_getglobal ; 
 int /*<<< orphan*/ * lua_geti ; 
 int /*<<< orphan*/ * lua_gettop ; 
 int /*<<< orphan*/ * lua_iscfunction ; 
 int /*<<< orphan*/ * lua_isinteger ; 
 int /*<<< orphan*/ * lua_isnumber ; 
 int /*<<< orphan*/ * lua_isstring ; 
 int /*<<< orphan*/ * lua_isuserdata ; 
 int /*<<< orphan*/ * lua_newthread ; 
 int /*<<< orphan*/ * lua_newuserdata ; 
 int /*<<< orphan*/ * lua_pcallk ; 
 int /*<<< orphan*/ * lua_pushcclosure ; 
 int /*<<< orphan*/ * lua_pushinteger ; 
 int /*<<< orphan*/ * lua_pushlstring ; 
 int /*<<< orphan*/ * lua_pushnumber ; 
 int /*<<< orphan*/ * lua_pushstring ; 
 int /*<<< orphan*/ * lua_pushvalue ; 
 int /*<<< orphan*/ * lua_resume ; 
 int /*<<< orphan*/ * lua_setfield ; 
 int /*<<< orphan*/ * lua_setglobal ; 
 int /*<<< orphan*/ * lua_seti ; 
 int /*<<< orphan*/ * lua_settop ; 
 int /*<<< orphan*/ * lua_toboolean ; 
 int /*<<< orphan*/ * lua_tointegerx ; 
 int /*<<< orphan*/ * lua_tolstring ; 
 int /*<<< orphan*/ * lua_tonumberx ; 
 int /*<<< orphan*/ * lua_type ; 
 int /*<<< orphan*/ * lua_typename ; 
 int /*<<< orphan*/ * lua_version ; 
 int /*<<< orphan*/ * lua_xmove ; 
 int /*<<< orphan*/ * lua_yieldk ; 
 int /*<<< orphan*/  stderr ; 

int stublua_init(void)
{
    void *lib = NULL;
    
    {
#if defined(__APPLE__)
        static const char *possible_names[] = {

            "liblua.5.3.5.dylib",
            "liblua.5.3.dylib",
            "liblua5.3.dylib",
            "liblua.dylib",
            0
        };
#elif defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
        static const char *possible_names[] = {
            "lua53.dll",
            "lua.dll",
            0
        };
#else
        static const char *possible_names[] = {
            "liblua5.3.so",
            "liblua5.3.so.0",
            "liblua5.3.so.0.0.0",
            0
        };
#endif
        unsigned i;
        for (i=0; possible_names[i]; i++) {
#if defined(WIN32)
            lib = LoadLibraryA(possible_names[i]);
#else
            lib = dlopen(possible_names[i], RTLD_LAZY);
#endif
            if (lib) {
                break;
            } else {
                ;
            }
        }
        
        if (lib == NULL) {
            fprintf(stderr, "liblua: failed to load Lua shared library\n");
            fprintf(stderr, "    HINT: you must install Lua library\n");
        }
    }

#if defined(WIN32)
#define DOLINK(name) \
    name = GetProcAddress(lib, #name); \
    if (name == NULL) fprintf(stderr, "liblua: %s: failed\n", #name);
#else
#define DOLINK(name) \
    name = dlsym(lib, #name); \
    if (name == NULL) fprintf(stderr, "liblua: %s: failed\n", #name);
#endif
    
    DOLINK(lua_version);
    
    
    DOLINK(lua_close)
    DOLINK(lua_getfield)
    DOLINK(lua_getglobal)
    DOLINK(lua_geti)
    DOLINK(lua_gettop)
    DOLINK(lua_isnumber);
    DOLINK(lua_isstring);
    DOLINK(lua_iscfunction);
    DOLINK(lua_isinteger);
    DOLINK(lua_isuserdata);
    DOLINK(lua_newthread)
    DOLINK(lua_newuserdata)
    DOLINK(lua_pcallk)
    DOLINK(lua_pushcclosure)
    DOLINK(lua_pushinteger)
    DOLINK(lua_pushlstring)
    DOLINK(lua_pushnumber)
    DOLINK(lua_pushstring)
    DOLINK(lua_pushvalue)
    DOLINK(lua_resume)
    DOLINK(lua_setfield)
    DOLINK(lua_setglobal)
    DOLINK(lua_seti)
    DOLINK(lua_settop)
    DOLINK(lua_toboolean)
    DOLINK(lua_tointegerx)
    DOLINK(lua_tolstring)
    DOLINK(lua_tonumberx)
    DOLINK(lua_type)
    DOLINK(lua_typename)
    DOLINK(lua_version)
    DOLINK(lua_xmove)
    DOLINK(lua_yieldk)
    
    DOLINK(luaL_checkinteger)
    DOLINK(luaL_checklstring)
    DOLINK(luaL_checkudata)
    DOLINK(luaL_len)
    DOLINK(luaL_loadbufferx)
    DOLINK(luaL_loadfilex)
    DOLINK(luaL_loadstring)
    DOLINK(luaL_newmetatable)
    DOLINK(luaL_newstate)
    DOLINK(luaL_openlibs)
    DOLINK(luaL_ref)
    DOLINK(luaL_setfuncs)
    DOLINK(luaL_setmetatable)
    DOLINK(luaL_unref)
    
    return 0;
}