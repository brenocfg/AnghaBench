#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  ud; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ lcontext ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite_ctx_meta_ref ; 

__attribute__((used)) static lcontext *lsqlite_make_context(lua_State *L) {
    lcontext *ctx = (lcontext*)lua_newuserdata(L, sizeof(lcontext));
    lua_rawgeti(L, LUA_REGISTRYINDEX, sqlite_ctx_meta_ref);
    lua_setmetatable(L, -2);
    ctx->ctx = NULL;
    ctx->ud = LUA_NOREF;
    return ctx;
}