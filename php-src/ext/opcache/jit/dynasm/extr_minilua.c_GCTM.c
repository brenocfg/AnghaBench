#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  allowhook; scalar_t__ top; } ;
typedef  TYPE_4__ lua_State ;
typedef  int lu_mem ;
typedef  int /*<<< orphan*/  lu_byte ;
struct TYPE_24__ {int GCthreshold; int totalbytes; TYPE_2__* mainthread; TYPE_7__* tmudata; } ;
typedef  TYPE_5__ global_State ;
struct TYPE_22__ {int /*<<< orphan*/  metatable; TYPE_7__* next; } ;
struct TYPE_25__ {TYPE_3__ uv; } ;
typedef  TYPE_6__ Udata ;
struct TYPE_20__ {TYPE_7__* next; } ;
struct TYPE_26__ {TYPE_1__ gch; } ;
struct TYPE_21__ {TYPE_7__* next; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_7__ GCObject ;

/* Variables and functions */
 TYPE_5__* G (TYPE_4__*) ; 
 int /*<<< orphan*/  TM_GC ; 
 int /*<<< orphan*/ * fasttm (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaD_call (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makewhite (TYPE_5__*,TYPE_7__*) ; 
 TYPE_6__* rawgco2u (TYPE_7__*) ; 
 int /*<<< orphan*/  setobj (TYPE_4__*,scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setuvalue (TYPE_4__*,scalar_t__,TYPE_6__*) ; 

__attribute__((used)) static void GCTM(lua_State*L){
global_State*g=G(L);
GCObject*o=g->tmudata->gch.next;
Udata*udata=rawgco2u(o);
const TValue*tm;
if(o==g->tmudata)
g->tmudata=NULL;
else
g->tmudata->gch.next=udata->uv.next;
udata->uv.next=g->mainthread->next;
g->mainthread->next=o;
makewhite(g,o);
tm=fasttm(L,udata->uv.metatable,TM_GC);
if(tm!=NULL){
lu_byte oldah=L->allowhook;
lu_mem oldt=g->GCthreshold;
L->allowhook=0;
g->GCthreshold=2*g->totalbytes;
setobj(L,L->top,tm);
setuvalue(L,L->top+1,udata);
L->top+=2;
luaD_call(L,L->top-2,0);
L->allowhook=oldah;
g->GCthreshold=oldt;
}
}