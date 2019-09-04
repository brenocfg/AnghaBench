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
struct TYPE_4__ {int /*<<< orphan*/  aggregate; } ;
typedef  TYPE_1__ sdb_func ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ lcontext ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lcontext_check_aggregate(lua_State *L, lcontext *ctx) {
    sdb_func *func = (sdb_func*)sqlite3_user_data(ctx->ctx);
    if (!func->aggregate) {
        luaL_error(L, "attempt to call aggregate method from scalar function");
    }
}