#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_18__ {int numparams; int is_vararg; } ;
typedef  int StkId ;
typedef  TYPE_2__ Proto ;

/* Variables and functions */
 int VARARG_HASARG ; 
 int VARARG_NEEDSARG ; 
 int /*<<< orphan*/  cast_num (int) ; 
 int /*<<< orphan*/  fixedstack (TYPE_1__*) ; 
 int /*<<< orphan*/  incr_top (TYPE_1__*) ; 
 int iswhite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaC_checkGC (TYPE_1__*) ; 
 int /*<<< orphan*/ * luaH_new (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  luaH_setnum (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaH_setstr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaS_newliteral (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sethvalue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sethvalue2s (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnilvalue (int) ; 
 int /*<<< orphan*/  setnvalue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj2n (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setobjs2s (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unfixedstack (TYPE_1__*) ; 

__attribute__((used)) static StkId adjust_varargs (lua_State *L, Proto *p, int actual) {
  int i;
  int nfixargs = p->numparams;
#if defined(LUA_COMPAT_VARARG)
  Table *htab = NULL;
#endif
  StkId base, fixed;
  for (; actual < nfixargs; ++actual)
    setnilvalue(L->top++);
#if defined(LUA_COMPAT_VARARG)
  if (p->is_vararg & VARARG_NEEDSARG) { /* compat. with old-style vararg? */
    int nvar = actual - nfixargs;  /* number of extra arguments */
    lua_assert(p->is_vararg & VARARG_HASARG);
    luaC_checkGC(L);
    htab = luaH_new(L, nvar, 1);  /* create `arg' table */
    sethvalue2s(L, L->top, htab); /* put table on stack */
    incr_top(L);
    fixedstack(L);
    for (i=0; i<nvar; i++)  /* put extra arguments into `arg' table */
      setobj2n(L, luaH_setnum(L, htab, i+1), L->top - 1 - nvar + i);
    unfixedstack(L);
    /* store counter in field `n' */
    setnvalue(luaH_setstr(L, htab, luaS_newliteral(L, "n")), cast_num(nvar));
    L->top--; /* remove table from stack */
  }
#endif
  /* move fixed parameters to final position */
  fixed = L->top - actual;  /* first fixed argument */
  base = L->top;  /* final position of first argument */
  for (i=0; i<nfixargs; i++) {
    setobjs2s(L, L->top++, fixed+i);
    setnilvalue(fixed+i);
  }
#if defined(LUA_COMPAT_VARARG)
  /* add `arg' parameter */
  if (htab) {
    sethvalue(L, L->top++, htab);
    lua_assert(iswhite(obj2gco(htab)));
  }
#endif
  return base;
}