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
struct lua_State {int dummy; } ;
struct TYPE_2__ {char* name; struct lua_State* L; } ;
struct Masscan {TYPE_1__ scripting; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int,char*,...) ; 
 int LUA_OK ; 
 int /*<<< orphan*/  exit (int) ; 
 int luaL_loadfile (struct lua_State*,char const*) ; 
 struct lua_State* luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (struct lua_State*) ; 
 int /*<<< orphan*/  lua_close (struct lua_State*) ; 
 int lua_pcall (struct lua_State*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tostring (struct lua_State*,int) ; 
 scalar_t__* lua_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scripting_masscan_init (struct Masscan*) ; 
 int /*<<< orphan*/  stublua_init () ; 

void
scripting_init(struct Masscan *masscan)
{
    int version;
    struct lua_State *L;
    const char *filename = masscan->scripting.name;
    int x;

    
    if (filename == 0 || filename[0] == '\0') {
        LOG(0, "%s: no script specified, use --script option\n", "SCRIPTING");
        exit(1);
    }
    
    /* Dynamically link the library */
    stublua_init();
    
    /* Test to see if the loading was successful */
    version = (int)*lua_version(0);
    LOG(1, "Lua version = %d\n", version);
    if (version != 503 && version != 502) {
        LOG(0, "Unable to load Lua library\n");
        exit(1);
    }
    
    /*
     * Create a Lua VM
     */
    L = luaL_newstate();
    luaL_openlibs(L);
    masscan->scripting.L = L;
    
    /*
     * TODO: Sanbox stuff
     */
    /* We need to do a bunch of sandboxing here to prevent hostile or badly
     * written scripts from disrupting the system */
    
    /*
     * Create the Masscan object
     */
    scripting_masscan_init(masscan);
    
    /*
     * Load the script. This will verify the syntax.
     */
    x = luaL_loadfile(L, filename);
    if (x != LUA_OK) {
        LOG(0, "%s error loading: %s: %s\n", "SCRIPTING:", filename, lua_tostring(L, -1));
        lua_close(L);
        exit(1);
    }
    
    /*
     * Lua: Start running the script. At this stage, the "onConnection()" function doesn't
     * run. Instead, it's registered as a global function to be called later.
     */
    LOG(1, "%s running script: %s\n", "SCRIPTING:", filename);
    x = lua_pcall(L, 0, 0, 0);
    if (x != LUA_OK) {
        LOG(0, "%s error running: %s: %s\n", "SCRIPTING:", filename, lua_tostring(L, -1));
        lua_close(L);
        exit(1);
    }

}