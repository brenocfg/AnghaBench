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
struct lua_State {int dummy; } ;
struct Banner1 {struct lua_State* L; } ;
typedef  int lua_Integer ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int luaL_len (struct lua_State*,int) ; 
 int /*<<< orphan*/  lua_getglobal (struct lua_State*,char*) ; 
 int /*<<< orphan*/  lua_geti (struct lua_State*,int,int) ; 
 scalar_t__ lua_isinteger (struct lua_State*,int) ; 
 scalar_t__ lua_isstring (struct lua_State*,int) ; 
 scalar_t__ lua_istable (struct lua_State*,int) ; 
 scalar_t__ lua_tointeger (struct lua_State*,int) ; 
 int /*<<< orphan*/  lua_tostring (struct lua_State*,int) ; 
 int /*<<< orphan*/  register_script_for_port (struct Banner1*,int) ; 
 int /*<<< orphan*/  register_script_for_ports (struct Banner1*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
scripting_banner_init(struct Banner1 *b)
{
    struct lua_State *L = b->L;
    
    /* Kludge: this gets called prematurely, without scripting, so
     * just return */
    if (L == NULL)
        return 0;
    
    LOG(0, "SCRIPTING: banner init          \n");
    
    /*
     * Register TCP ports to run on
     */
    lua_getglobal(L, "setTcpPorts");
    if (lua_isstring(L, -1)) {
        register_script_for_ports(b, lua_tostring(L, -1));
    } else if (lua_isinteger(L, -1)) {
        register_script_for_port(b, (int)lua_tointeger(L, -1));
    } else if (lua_istable(L, -1)) {
        lua_Integer n = luaL_len(L, -1);
        int i;
        for (i=1; i<=n; i++) {
            lua_geti(L, -1, i);
            if (lua_isstring(L, -1)) {
                register_script_for_ports(b, lua_tostring(L, -1));
            } else if (lua_isinteger(L, -1)) {
                register_script_for_port(b, (int)lua_tointeger(L, -1));
            }
        }
    }
    
    return 0;
}