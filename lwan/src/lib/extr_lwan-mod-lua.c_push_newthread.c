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
struct coro {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  coro_defer2 (struct coro*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_newthread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unref_thread ; 

__attribute__((used)) static lua_State *push_newthread(lua_State *L, struct coro *coro)
{
    lua_State *L1 = lua_newthread(L);

    if (UNLIKELY(!L1))
        return NULL;

    int thread_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    coro_defer2(coro, unref_thread, L, (void *)(intptr_t)thread_ref);

    return L1;
}