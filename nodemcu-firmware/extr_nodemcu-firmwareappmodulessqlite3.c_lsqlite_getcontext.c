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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lcontext ;

/* Variables and functions */
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_typerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  sqlite_ctx_meta ; 

__attribute__((used)) static lcontext *lsqlite_getcontext(lua_State *L, int index) {
    lcontext *ctx = (lcontext*)luaL_checkudata(L, index, sqlite_ctx_meta);
    if (ctx == NULL) luaL_typerror(L, index, "sqlite context");
    return ctx;
}