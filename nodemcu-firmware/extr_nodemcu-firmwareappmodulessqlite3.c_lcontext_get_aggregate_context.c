#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  ud; } ;
typedef  TYPE_1__ lcontext ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lcontext_check_aggregate (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* lsqlite_checkcontext (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lcontext_get_aggregate_context(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    lcontext_check_aggregate(L, ctx);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->ud);
    return 1;
}