#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct LexState {int /*<<< orphan*/ * fs; int /*<<< orphan*/ * buff; } ;
struct FuncState {TYPE_2__* f; int /*<<< orphan*/ * prev; } ;
struct TYPE_11__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  ZIO ;
struct TYPE_12__ {scalar_t__ nups; int /*<<< orphan*/  is_vararg; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_2__ Proto ;
typedef  int /*<<< orphan*/  Mbuffer ;

/* Variables and functions */
 int /*<<< orphan*/  TK_EOS ; 
 int /*<<< orphan*/  VARARG_ISVARARG ; 
 int /*<<< orphan*/  check (struct LexState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk (struct LexState*) ; 
 int /*<<< orphan*/  close_func (struct LexState*) ; 
 int /*<<< orphan*/  compile_stripdebug (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/ * luaS_new (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  luaX_next (struct LexState*) ; 
 int /*<<< orphan*/  luaX_setinput (TYPE_1__*,struct LexState*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  open_func (struct LexState*,struct FuncState*) ; 
 int /*<<< orphan*/  setsvalue2s (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Proto *luaY_parser (lua_State *L, ZIO *z, Mbuffer *buff, const char *name) {
  struct LexState lexstate;
  struct FuncState funcstate;
  TString *tname = luaS_new(L, name);
  setsvalue2s(L, L->top, tname);  /* protect name */
  incr_top(L);
  lexstate.buff = buff;
  luaX_setinput(L, &lexstate, z, tname);
  open_func(&lexstate, &funcstate);
  funcstate.f->is_vararg = VARARG_ISVARARG;  /* main func. is always vararg */
  luaX_next(&lexstate);  /* read first token */
  chunk(&lexstate);
  check(&lexstate, TK_EOS);
  close_func(&lexstate);
#ifdef LUA_OPTIMIZE_DEBUG
  compile_stripdebug(L, funcstate.f);
#endif
  L->top--; /* remove 'name' from stack */
  lua_assert(funcstate.prev == NULL);
  lua_assert(funcstate.f->nups == 0);
  lua_assert(lexstate.fs == NULL);
  return funcstate.f;
}