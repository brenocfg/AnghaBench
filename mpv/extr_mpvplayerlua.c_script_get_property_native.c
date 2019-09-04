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
typedef  int /*<<< orphan*/  mpv_node ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_NODE ; 
 int /*<<< orphan*/  auto_free_node (void*,int /*<<< orphan*/ *) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 void* mp_lua_PITA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_lua_optarg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpv_error_string (int) ; 
 int mpv_get_property (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pushnode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free_children (void*) ; 

__attribute__((used)) static int script_get_property_native(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    const char *name = luaL_checkstring(L, 1);
    mp_lua_optarg(L, 2);
    void *tmp = mp_lua_PITA(L);

    mpv_node node;
    int err = mpv_get_property(ctx->client, name, MPV_FORMAT_NODE, &node);
    if (err >= 0) {
        auto_free_node(tmp, &node);
        pushnode(L, &node);
        talloc_free_children(tmp);
        return 1;
    }
    lua_pushvalue(L, 2);
    lua_pushstring(L, mpv_error_string(err));
    return 2;
}