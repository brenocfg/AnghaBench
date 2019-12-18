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
typedef  struct lwan_request lwan_request ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 struct lwan_request* lwan_lua_get_request_from_userdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int request_param_getter(lua_State *L,
                                const char *(*getter)(struct lwan_request *req,
                                                      const char *key))
{
    struct lwan_request *request = lwan_lua_get_request_from_userdata(L);
    const char *key_str = lua_tostring(L, -1);

    const char *value = getter(request, key_str);
    if (!value)
        lua_pushnil(L);
    else
        lua_pushstring(L, value);

    return 1;
}