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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {TYPE_1__* fs; int /*<<< orphan*/ * L; } ;
struct TYPE_4__ {int /*<<< orphan*/  h; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  luaC_checkGC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaH_setstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaS_newlstr (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  setbvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/ *) ; 

TString *luaX_newstring (LexState *ls, const char *str, size_t l) {
  lua_State *L = ls->L;
  TString *ts = luaS_newlstr(L, str, l);
  TValue *o = luaH_setstr(L, ls->fs->h, ts);  /* entry for `str' */
  if (ttisnil(o)) {
    setbvalue(o, 1);  /* make sure `str' will not be collected */
    luaC_checkGC(L);
  }
  return ts;
}