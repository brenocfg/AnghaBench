#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_20__ {scalar_t__ flags; int /*<<< orphan*/  metatable; } ;
typedef  TYPE_2__ Table ;
typedef  int /*<<< orphan*/  const TValue ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int MAXTAGLOOP ; 
 int /*<<< orphan*/  TM_NEWINDEX ; 
 int /*<<< orphan*/  callTM (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* fasttm (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixedstack (TYPE_1__*) ; 
 TYPE_2__* hvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  luaC_barriert (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaG_runerror (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  luaG_typeerror (TYPE_1__*,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  const* luaH_set (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* luaT_gettmbyobj (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilvalue (scalar_t__) ; 
 int /*<<< orphan*/  setobj (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setobj2s (TYPE_1__*,scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setobj2t (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ttisfunction (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttislightfunction (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisrotable (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttistable (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  unfixedstack (TYPE_1__*) ; 

void luaV_settable (lua_State *L, const TValue *t, TValue *key, StkId val) {
  int loop;
  TValue temp;
  setnilvalue(L->top);
  L->top++;
  fixedstack(L);
  for (loop = 0; loop < MAXTAGLOOP; loop++) {
    const TValue *tm = NULL;
    if (ttistable(t)) {  /* `t' is a table? */
      Table *h = hvalue(t);
      TValue *oldval = luaH_set(L, h, key); /* do a primitive set */
      if ((!ttisnil(oldval)) ||  /* result is no nil? */
          (tm = fasttm(L, h->metatable, TM_NEWINDEX)) == NULL) {
        L->top--;
        unfixedstack(L);
        setobj2t(L, oldval, val);
        ((Table *)h)->flags = 0;
        luaC_barriert(L, (Table*)h, val);
        return;
      }
      /* else will try the tag method */
    }
    else if (ttisrotable(t)) {
      luaG_runerror(L, "invalid write to ROM variable");
    }
    else if (ttisnil(tm = luaT_gettmbyobj(L, t, TM_NEWINDEX)))
      luaG_typeerror(L, t, "index");

    if (ttisfunction(tm) || ttislightfunction(tm)) {
      L->top--;
      unfixedstack(L);
      callTM(L, tm, t, key, val);
      return;
    }
    /* else repeat with `tm' */
    setobj(L, &temp, tm);  /* avoid pointing inside table (may rehash) */
    t = &temp;
    setobj2s(L, L->top-1, t);  /* need to protect value from EGC. */
  }
  luaG_runerror(L, "loop in settable");
}