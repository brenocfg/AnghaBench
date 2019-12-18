#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  weak; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_12__ {int marked; int sizearray; int /*<<< orphan*/ * array; int /*<<< orphan*/  gclist; scalar_t__ metatable; } ;
typedef  TYPE_2__ Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  TM_MODE ; 
 int bitmask (int) ; 
 int cast_byte (int) ; 
 int /*<<< orphan*/ * gfasttm (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gnode (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * gval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  markobject (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  markvalue (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obj2gco (TYPE_2__*) ; 
 int /*<<< orphan*/  removeentry (int /*<<< orphan*/ *) ; 
 int sizenode (TYPE_2__*) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  svalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ ttisstring (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int traversetable(global_State*g,Table*h){
int i;
int weakkey=0;
int weakvalue=0;
const TValue*mode;
if(h->metatable)
markobject(g,h->metatable);
mode=gfasttm(g,h->metatable,TM_MODE);
if(mode&&ttisstring(mode)){
weakkey=(strchr(svalue(mode),'k')!=NULL);
weakvalue=(strchr(svalue(mode),'v')!=NULL);
if(weakkey||weakvalue){
h->marked&=~(bitmask(3)|bitmask(4));
h->marked|=cast_byte((weakkey<<3)|
(weakvalue<<4));
h->gclist=g->weak;
g->weak=obj2gco(h);
}
}
if(weakkey&&weakvalue)return 1;
if(!weakvalue){
i=h->sizearray;
while(i--)
markvalue(g,&h->array[i]);
}
i=sizenode(h);
while(i--){
Node*n=gnode(h,i);
if(ttisnil(gval(n)))
removeentry(n);
else{
if(!weakkey)markvalue(g,gkey(n));
if(!weakvalue)markvalue(g,gval(n));
}
}
return weakkey||weakvalue;
}