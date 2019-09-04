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
struct script_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct script_ctx*,char*) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int script_suspend(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    MP_ERR(ctx, "mp.suspend() is deprecated and does nothing.\n");
    return 0;
}