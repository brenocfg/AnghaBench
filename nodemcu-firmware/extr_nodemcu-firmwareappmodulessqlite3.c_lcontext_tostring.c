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
struct TYPE_3__ {int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ lcontext ;

/* Variables and functions */
 int /*<<< orphan*/  c_sprintf (char*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* lsqlite_getcontext (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int lcontext_tostring(lua_State *L) {
    char buff[39];
    lcontext *ctx = lsqlite_getcontext(L, 1);
    if (ctx->ctx == NULL)
        strcpy(buff, "closed");
    else
        c_sprintf(buff, "%p", ctx->ctx);
    lua_pushfstring(L, "sqlite function context (%s)", buff);
    return 1;
}