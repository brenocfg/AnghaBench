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
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  luaG_typeerror (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ ttisnumber (int /*<<< orphan*/ ) ; 
 scalar_t__ ttisstring (int /*<<< orphan*/ ) ; 

void luaG_concaterror (lua_State *L, StkId p1, StkId p2) {
  if (ttisstring(p1) || ttisnumber(p1)) p1 = p2;
  lua_assert(!ttisstring(p1) && !ttisnumber(p1));
  luaG_typeerror(L, p1, "concatenate");
}