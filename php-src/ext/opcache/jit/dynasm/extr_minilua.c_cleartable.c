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
struct TYPE_5__ {int sizearray; int /*<<< orphan*/ * gclist; int /*<<< orphan*/ * array; int /*<<< orphan*/  marked; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_1__* gco2h (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gnode (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * gval (int /*<<< orphan*/ *) ; 
 scalar_t__ iscleared (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * key2tval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  removeentry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnilvalue (int /*<<< orphan*/ *) ; 
 int sizenode (TYPE_1__*) ; 
 scalar_t__ testbit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleartable(GCObject*l){
while(l){
Table*h=gco2h(l);
int i=h->sizearray;
if(testbit(h->marked,4)){
while(i--){
TValue*o=&h->array[i];
if(iscleared(o,0))
setnilvalue(o);
}
}
i=sizenode(h);
while(i--){
Node*n=gnode(h,i);
if(!ttisnil(gval(n))&&
(iscleared(key2tval(n),1)||iscleared(gval(n),0))){
setnilvalue(gval(n));
removeentry(n);
}
}
l=h->gclist;
}
}