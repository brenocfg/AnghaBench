#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_14__ {TYPE_4__* tmudata; TYPE_1__* mainthread; } ;
typedef  TYPE_3__ global_State ;
struct TYPE_16__ {int /*<<< orphan*/  metatable; } ;
struct TYPE_13__ {TYPE_4__* next; } ;
struct TYPE_15__ {TYPE_2__ gch; } ;
struct TYPE_12__ {TYPE_4__* next; } ;
typedef  TYPE_4__ GCObject ;

/* Variables and functions */
 TYPE_3__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TM_GC ; 
 int /*<<< orphan*/ * fasttm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* gco2u (TYPE_4__*) ; 
 scalar_t__ isfinalized (TYPE_5__*) ; 
 scalar_t__ iswhite (TYPE_4__*) ; 
 int /*<<< orphan*/  markfinalized (TYPE_5__*) ; 
 scalar_t__ sizeudata (TYPE_5__*) ; 

__attribute__((used)) static size_t luaC_separateudata(lua_State*L,int all){
global_State*g=G(L);
size_t deadmem=0;
GCObject**p=&g->mainthread->next;
GCObject*curr;
while((curr=*p)!=NULL){
if(!(iswhite(curr)||all)||isfinalized(gco2u(curr)))
p=&curr->gch.next;
else if(fasttm(L,gco2u(curr)->metatable,TM_GC)==NULL){
markfinalized(gco2u(curr));
p=&curr->gch.next;
}
else{
deadmem+=sizeudata(gco2u(curr));
markfinalized(gco2u(curr));
*p=curr->gch.next;
if(g->tmudata==NULL)
g->tmudata=curr->gch.next=curr;
else{
curr->gch.next=g->tmudata->gch.next;
g->tmudata->gch.next=curr;
g->tmudata=curr;
}
}
}
return deadmem;
}