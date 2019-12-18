#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {int top; TYPE_5__* ci; } ;
typedef  TYPE_4__ lua_State ;
struct TYPE_14__ {int base; } ;
struct TYPE_15__ {TYPE_1__ l; } ;
struct TYPE_18__ {int func; TYPE_3__* next; TYPE_2__ u; } ;
struct TYPE_16__ {int func; } ;
struct TYPE_13__ {int /*<<< orphan*/  p; } ;
typedef  int StkId ;
typedef  TYPE_5__ CallInfo ;

/* Variables and functions */
 TYPE_11__* ci_func (TYPE_5__*) ; 
 int /*<<< orphan*/  currentpc (TYPE_5__*) ; 
 char const* findvararg (TYPE_5__*,int,int*) ; 
 scalar_t__ isLua (TYPE_5__*) ; 
 char* luaF_getlocalname (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *findlocal (lua_State *L, CallInfo *ci, int n,
                              StkId *pos) {
  const char *name = NULL;
  StkId base;
  if (isLua(ci)) {
    if (n < 0)  /* access to vararg values? */
      return findvararg(ci, -n, pos);
    else {
      base = ci->u.l.base;
      name = luaF_getlocalname(ci_func(ci)->p, n, currentpc(ci));
    }
  }
  else
    base = ci->func + 1;
  if (name == NULL) {  /* no 'standard' name? */
    StkId limit = (ci == L->ci) ? L->top : ci->next->func;
    if (limit - base >= n && n > 0)  /* is 'n' inside 'ci' stack? */
      name = "(*temporary)";  /* generic name for any valid slot */
    else
      return NULL;  /* no name */
  }
  *pos = base + (n - 1);
  return name;
}