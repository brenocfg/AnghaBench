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
struct TYPE_6__ {int sizearray; scalar_t__ node; int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__ Table ;

/* Variables and functions */
 int /*<<< orphan*/  TValue ; 
 scalar_t__ dummynode ; 
 int /*<<< orphan*/  luaH_setnum (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  luaM_reallocvector (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resize_hashpart (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  setarrayvector (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  setobjt2t (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resize (lua_State *L, Table *t, int nasize, int nhsize) {
  int i;
  int oldasize = t->sizearray;
  if (nasize > oldasize)  /* array part must grow? */
    setarrayvector(L, t, nasize);
  if (t->node != dummynode || nhsize>0)
    resize_hashpart(L, t, nhsize);
  if (nasize < oldasize) {  /* array part must shrink? */
    t->sizearray = nasize;
    /* re-insert elements from vanishing slice */
    for (i=nasize; i<oldasize; i++) {
      if (!ttisnil(&t->array[i]))
        setobjt2t(L, luaH_setnum(L, t, i+1), &t->array[i]);
    }
    /* shrink array */
    luaM_reallocvector(L, t->array, oldasize, nasize, TValue);
  }
}