#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
struct TYPE_18__ {int base; } ;
typedef  TYPE_1__ lua_State ;
typedef  scalar_t__ lu_mem ;
struct TYPE_20__ {size_t n; } ;
struct TYPE_19__ {size_t len; } ;
struct TYPE_17__ {scalar_t__ memlimit; TYPE_6__ buff; } ;
typedef  int StkId ;

/* Variables and functions */
 TYPE_15__* G (TYPE_1__*) ; 
 scalar_t__ MAX_SIZET ; 
 int /*<<< orphan*/  TM_CONCAT ; 
 int /*<<< orphan*/  call_binTM (TYPE_1__*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixedstack (TYPE_1__*) ; 
 int /*<<< orphan*/  luaG_concaterror (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  luaG_runerror (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  luaS_newlstr (TYPE_1__*,char*,size_t) ; 
 char* luaZ_openspace (TYPE_1__*,TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  luaZ_resetbuffer (TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  setsvalue2s (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svalue (int) ; 
 scalar_t__ tostring (TYPE_1__*,int) ; 
 TYPE_3__* tsvalue (int) ; 
 scalar_t__ ttisnumber (int) ; 
 scalar_t__ ttisstring (int) ; 
 int /*<<< orphan*/  unfixedstack (TYPE_1__*) ; 

void luaV_concat (lua_State *L, int total, int last) {
  lu_mem max_sizet = MAX_SIZET;
  if (G(L)->memlimit < max_sizet) max_sizet = G(L)->memlimit;
  do {
    /* Any call which does a memory allocation may trim the stack,
       invalidating top unless the stack is fixed during the allocation */
    StkId top = L->base + last + 1;
    fixedstack(L);
    int n = 2;  /* number of elements handled in this pass (at least 2) */
    if (!(ttisstring(top-2) || ttisnumber(top-2)) || !tostring(L, top-1)) {
      unfixedstack(L);
      if (!call_binTM(L, top-2, top-1, top-2, TM_CONCAT)) {
        /* restore 'top' pointer, since stack might have been reallocted */
        top = L->base + last + 1;
        luaG_concaterror(L, top-2, top-1);
      }
    } else if (tsvalue(top-1)->len == 0) { /* second op is empty? */
      (void)tostring(L, top - 2);  /* result is first op (as string) */
    } else {
      /* at least two string values; get as many as possible */
      size_t tl = tsvalue(top-1)->len;
      char *buffer;
      int i;
      /* collect total length */
      for (n = 1; n < total && tostring(L, top-n-1); n++) {
        size_t l = tsvalue(top-n-1)->len;
        if (l >= max_sizet - tl) luaG_runerror(L, "string length overflow");
        tl += l;
      }
      G(L)->buff.n = tl;
      buffer = luaZ_openspace(L, &G(L)->buff, tl);
      tl = 0;
      for (i=n; i>0; i--) {  /* concat all strings */
        size_t l = tsvalue(top-i)->len;
        memcpy(buffer+tl, svalue(top-i), l);
        tl += l;
      }
      setsvalue2s(L, top-n, luaS_newlstr(L, buffer, tl));
      luaZ_resetbuffer(&G(L)->buff);
    }
    total -= n-1;  /* got `n' strings to create 1 new */
    last -= n-1;
    unfixedstack(L);
  } while (total > 1);  /* repeat until only 1 result left */
}