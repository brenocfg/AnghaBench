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
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ lcontext ;

/* Variables and functions */
 TYPE_1__* lsqlite_checkcontext (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lcontext_result_null(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    sqlite3_result_null(ctx->ctx);
    return 0;
}