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
struct mpv_node {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_NODE ; 
 int check_error (int /*<<< orphan*/ *,int) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  makenode (void*,struct mpv_node*,int /*<<< orphan*/ *,int) ; 
 void* mp_lua_PITA (int /*<<< orphan*/ *) ; 
 int mpv_set_property (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct mpv_node*) ; 
 int /*<<< orphan*/  talloc_free_children (void*) ; 

__attribute__((used)) static int script_set_property_native(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    const char *p = luaL_checkstring(L, 1);
    struct mpv_node node;
    void *tmp = mp_lua_PITA(L);
    makenode(tmp, &node, L, 2);
    int res = mpv_set_property(ctx->client, p, MPV_FORMAT_NODE, &node);
    talloc_free_children(tmp);
    return check_error(L, res);

}