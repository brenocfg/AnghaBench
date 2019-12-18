#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  UpVal ;
struct TYPE_4__ {int nupvalues; int /*<<< orphan*/ ** upvals; } ;
typedef  TYPE_1__ LClosure ;

/* Variables and functions */
 int /*<<< orphan*/  luaC_upvdeccount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaM_freemem (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeLclosure (int) ; 

__attribute__((used)) static void freeLclosure (lua_State *L, LClosure *cl) {
  int i;
  for (i = 0; i < cl->nupvalues; i++) {
    UpVal *uv = cl->upvals[i];
    if (uv)
      luaC_upvdeccount(L, uv);
  }
  luaM_freemem(L, cl, sizeLclosure(cl->nupvalues));
}