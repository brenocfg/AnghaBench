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
 int /*<<< orphan*/  auto_free_node (void*,struct mpv_node*) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  makenode (void*,struct mpv_node*,int /*<<< orphan*/ *,int) ; 
 void* mp_lua_PITA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_lua_optarg (int /*<<< orphan*/ *,int) ; 
 int mpv_command_node (int /*<<< orphan*/ ,struct mpv_node*,struct mpv_node*) ; 
 int /*<<< orphan*/  mpv_error_string (int) ; 
 int /*<<< orphan*/  pushnode (int /*<<< orphan*/ *,struct mpv_node*) ; 
 int /*<<< orphan*/  talloc_free_children (void*) ; 

__attribute__((used)) static int script_command_native(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    mp_lua_optarg(L, 2);
    struct mpv_node node;
    struct mpv_node result;
    void *tmp = mp_lua_PITA(L);
    makenode(tmp, &node, L, 1);
    int err = mpv_command_node(ctx->client, &node, &result);
    if (err >= 0) {
        auto_free_node(tmp, &result);
        pushnode(L, &result);
        talloc_free_children(tmp);
        return 1;
    }
    lua_pushvalue(L, 2);
    lua_pushstring(L, mpv_error_string(err));
    return 2;
}