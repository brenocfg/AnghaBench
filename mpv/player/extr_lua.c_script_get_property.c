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
struct script_ctx {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int MPV_FORMAT_OSD_STRING ; 
 int MPV_FORMAT_STRING ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 char* mpv_error_string (int) ; 
 int mpv_get_property (int /*<<< orphan*/ ,char const*,int,char**) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static int script_get_property(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    const char *name = luaL_checkstring(L, 1);
    int type = lua_tointeger(L, lua_upvalueindex(1))
               ? MPV_FORMAT_OSD_STRING : MPV_FORMAT_STRING;

    char *result = NULL;
    int err = mpv_get_property(ctx->client, name, type, &result);
    if (err >= 0) {
        lua_pushstring(L, result);
        talloc_free(result);
        return 1;
    } else {
        if (lua_isnoneornil(L, 2) && type == MPV_FORMAT_OSD_STRING) {
            lua_pushstring(L, "");
        } else {
            lua_pushvalue(L, 2);
        }
        lua_pushstring(L, mpv_error_string(err));
        return 2;
    }
}