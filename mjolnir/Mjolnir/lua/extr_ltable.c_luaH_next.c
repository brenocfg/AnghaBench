#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {unsigned int sizearray; int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__ Table ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
 scalar_t__ cast_int (unsigned int) ; 
 unsigned int findindex (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * gkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnode (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/ * gval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setivalue (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  setobj2s (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ sizenode (TYPE_1__*) ; 
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/ *) ; 

int luaH_next (lua_State *L, Table *t, StkId key) {
  unsigned int i = findindex(L, t, key);  /* find original element */
  for (; i < t->sizearray; i++) {  /* try first array part */
    if (!ttisnil(&t->array[i])) {  /* a non-nil value? */
      setivalue(key, i + 1);
      setobj2s(L, key+1, &t->array[i]);
      return 1;
    }
  }
  for (i -= t->sizearray; cast_int(i) < sizenode(t); i++) {  /* hash part */
    if (!ttisnil(gval(gnode(t, i)))) {  /* a non-nil value? */
      setobj2s(L, key, gkey(gnode(t, i)));
      setobj2s(L, key+1, gval(gnode(t, i)));
      return 1;
    }
  }
  return 0;  /* no more elements */
}