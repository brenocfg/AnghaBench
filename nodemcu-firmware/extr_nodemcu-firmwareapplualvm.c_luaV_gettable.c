#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {struct TYPE_5__* metatable; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int MAXTAGLOOP ; 
 int /*<<< orphan*/  TM_INDEX ; 
 int /*<<< orphan*/  callTMres (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fasttm (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* hvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  luaG_runerror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaG_typeerror (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * luaH_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaH_get_ro (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ luaR_getmeta (void*) ; 
 int /*<<< orphan*/ * luaT_gettmbyobj (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 void* rvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setobj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setobj2s (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisfunction (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttislightfunction (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisrotable (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttistable (int /*<<< orphan*/  const*) ; 

void luaV_gettable (lua_State *L, const TValue *t, TValue *key, StkId val) {
  int loop;
  TValue temp;
  for (loop = 0; loop < MAXTAGLOOP; loop++) {
    const TValue *tm;

    if (ttistable(t)) {  /* `t' is a table? */
      Table *h = hvalue(t);
      const TValue *res = luaH_get(h, key); /* do a primitive get */
      if (!ttisnil(res) ||  /* result is no nil? */
          (tm = fasttm(L, h->metatable, TM_INDEX)) == NULL) { /* or no TM? */
        setobj2s(L, val, res);
        return;
      }
      /* else will try the tag method */
    } else if (ttisrotable(t)) {  /* `t' is a table? */
      void *h = rvalue(t);
      const TValue *res = luaH_get_ro(h, key); /* do a primitive get */
      if (!ttisnil(res) ||  /* result is no nil? */
          (tm = fasttm(L, (Table*)luaR_getmeta(h), TM_INDEX)) == NULL) { /* or no TM? */
        setobj2s(L, val, res);
        return;
      }
      /* else will try the tag method */
    }
    else if (ttisnil(tm = luaT_gettmbyobj(L, t, TM_INDEX)))
        luaG_typeerror(L, t, "index");

    if (ttisfunction(tm) || ttislightfunction(tm)) {
      callTMres(L, val, tm, t, key);
      return;
    }
    /* else repeat with `tm' */
    setobj(L, &temp, tm);  /* avoid pointing inside table (may rehash) */
    t = &temp;
  }
  luaG_runerror(L, "loop in gettable");
}