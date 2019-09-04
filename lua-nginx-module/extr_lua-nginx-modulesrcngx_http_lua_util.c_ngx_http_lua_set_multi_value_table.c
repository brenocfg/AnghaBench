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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 

void
ngx_http_lua_set_multi_value_table(lua_State *L, int index)
{
    if (index < 0) {
        index = lua_gettop(L) + index + 1;
    }

    lua_pushvalue(L, -2); /* stack: table key value key */
    lua_rawget(L, index);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1); /* stack: table key value */
        lua_rawset(L, index); /* stack: table */

    } else {
        if (!lua_istable(L, -1)) {
            /* just inserted one value */
            lua_createtable(L, 4, 0);
                /* stack: table key value value table */
            lua_insert(L, -2);
                /* stack: table key value table value */
            lua_rawseti(L, -2, 1);
                /* stack: table key value table */
            lua_insert(L, -2);
                /* stack: table key table value */

            lua_rawseti(L, -2, 2); /* stack: table key table */

            lua_rawset(L, index); /* stack: table */

        } else {
            /* stack: table key value table */
            lua_insert(L, -2); /* stack: table key table value */

            lua_rawseti(L, -2, lua_objlen(L, -2) + 1);
                /* stack: table key table  */
            lua_pop(L, 2); /* stack: table */
        }
    }
}