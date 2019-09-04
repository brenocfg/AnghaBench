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
typedef  int /*<<< orphan*/  uint64_t ;
struct script_ctx {int /*<<< orphan*/  client; } ;
struct mpv_node {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int check_error (int /*<<< orphan*/ *,int) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  makenode (void*,struct mpv_node*,int /*<<< orphan*/ *,int) ; 
 void* mp_lua_PITA (int /*<<< orphan*/ *) ; 
 int mpv_command_node_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mpv_node*) ; 
 int /*<<< orphan*/  talloc_free_children (void*) ; 

__attribute__((used)) static int script_raw_command_native_async(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    uint64_t id = luaL_checknumber(L, 1);
    struct mpv_node node;
    void *tmp = mp_lua_PITA(L);
    makenode(tmp, &node, L, 2);
    int res = mpv_command_node_async(ctx->client, id, &node);
    talloc_free_children(tmp);
    return check_error(L, res);
}