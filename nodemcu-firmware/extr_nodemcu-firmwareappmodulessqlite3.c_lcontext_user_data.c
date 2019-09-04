#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  udata; } ;
typedef  TYPE_1__ sdb_func ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ lcontext ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 TYPE_2__* lsqlite_checkcontext (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lcontext_user_data(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    sdb_func *func = (sdb_func*)sqlite3_user_data(ctx->ctx);
    lua_rawgeti(L, LUA_REGISTRYINDEX, func->udata);
    return 1;
}