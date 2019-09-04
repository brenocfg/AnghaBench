#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_9__ {int /*<<< orphan*/  metatable; } ;
struct TYPE_8__ {int /*<<< orphan*/  metatable; } ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
#define  LUA_TBOOLEAN 135 
#define  LUA_TLIGHTFUNCTION 134 
#define  LUA_TLIGHTUSERDATA 133 
#define  LUA_TNIL 132 
#define  LUA_TNUMBER 131 
#define  LUA_TROTABLE 130 
#define  LUA_TTABLE 129 
#define  LUA_TUSERDATA 128 
 int /*<<< orphan*/  TM_EQ ; 
 int /*<<< orphan*/  bvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  callTMres (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gcvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * get_compTM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* hvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  l_isfalse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int luai_numeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rvalue (int /*<<< orphan*/  const*) ; 
 int ttype (int /*<<< orphan*/  const*) ; 
 TYPE_2__* uvalue (int /*<<< orphan*/  const*) ; 

int luaV_equalval (lua_State *L, const TValue *t1, const TValue *t2) {
  const TValue *tm;
  lua_assert(ttype(t1) == ttype(t2));
  switch (ttype(t1)) {
    case LUA_TNIL: return 1;
    case LUA_TNUMBER: return luai_numeq(nvalue(t1), nvalue(t2));
    case LUA_TBOOLEAN: return bvalue(t1) == bvalue(t2);  /* true must be 1 !! */
    case LUA_TROTABLE:
      return rvalue(t1) == rvalue(t2);
    case LUA_TLIGHTUSERDATA:
    case LUA_TLIGHTFUNCTION:
      return pvalue(t1) == pvalue(t2);
    case LUA_TUSERDATA: {
      if (uvalue(t1) == uvalue(t2)) return 1;
      tm = get_compTM(L, uvalue(t1)->metatable, uvalue(t2)->metatable,
                         TM_EQ);
      break;  /* will try TM */
    }
    case LUA_TTABLE: {
      if (hvalue(t1) == hvalue(t2)) return 1;
      tm = get_compTM(L, hvalue(t1)->metatable, hvalue(t2)->metatable, TM_EQ);
      break;  /* will try TM */
    }
    default: return gcvalue(t1) == gcvalue(t2);
  }
  if (tm == NULL) return 0;  /* no TM? */
  callTMres(L, L->top, tm, t1, t2);  /* call TM */
  return !l_isfalse(L->top);
}