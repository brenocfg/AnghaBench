#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  top; TYPE_1__* ci; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_8__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int LUA_ERRRUN ; 
 int /*<<< orphan*/  incr_top (TYPE_2__*) ; 
 int /*<<< orphan*/  luaS_new (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  lua_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  setsvalue2s (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resume_error (lua_State *L, const char *msg) {
  L->top = L->ci->base;
  setsvalue2s(L, L->top, luaS_new(L, msg));
  incr_top(L);
  lua_unlock(L);
  return LUA_ERRRUN;
}