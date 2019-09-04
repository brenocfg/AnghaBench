#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct MPContext {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {struct MPContext* mpctx; } ;

/* Variables and functions */
 TYPE_1__* get_ctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct MPContext *get_mpctx(lua_State *L)
{
    return get_ctx(L)->mpctx;
}