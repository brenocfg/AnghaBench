#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_8__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
#define  LUA_ERRERR 131 
#define  LUA_ERRMEM 130 
#define  LUA_ERRRUN 129 
#define  LUA_ERRSYNTAX 128 
 char* MEMERRMSG ; 
 int /*<<< orphan*/  luaS_newliteral (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  restorestack (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savestack (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  setobjs2s (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  setsvalue2s (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void luaD_seterrorobj (lua_State *L, int errcode, StkId oldtop) {
  switch (errcode) {
    case LUA_ERRMEM: {
      ptrdiff_t oldtopr = savestack(L, oldtop);
      setsvalue2s(L, restorestack(L, oldtopr), luaS_newliteral(L, MEMERRMSG));
      break;
    }
    case LUA_ERRERR: {
      ptrdiff_t oldtopr = savestack(L, oldtop);
      setsvalue2s(L, restorestack(L, oldtopr), luaS_newliteral(L, "error in error handling"));
      break;
    }
    case LUA_ERRSYNTAX:
    case LUA_ERRRUN: {
      setobjs2s(L, oldtop, L->top - 1);  /* error message on current top */
      break;
    }
  }
  L->top = oldtop + 1;
}