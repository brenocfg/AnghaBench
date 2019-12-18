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
 int /*<<< orphan*/  TM_EQ ; 
 int /*<<< orphan*/  bvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  callTMres (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gcvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * get_compTM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* hvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  l_isfalse (int /*<<< orphan*/ ) ; 
 int luai_numeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pvalue (int /*<<< orphan*/  const*) ; 
 int ttype (int /*<<< orphan*/  const*) ; 
 TYPE_2__* uvalue (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int luaV_equalval(lua_State*L,const TValue*t1,const TValue*t2){
const TValue*tm;
switch(ttype(t1)){
case 0:return 1;
case 3:return luai_numeq(nvalue(t1),nvalue(t2));
case 1:return bvalue(t1)==bvalue(t2);
case 2:return pvalue(t1)==pvalue(t2);
case 7:{
if(uvalue(t1)==uvalue(t2))return 1;
tm=get_compTM(L,uvalue(t1)->metatable,uvalue(t2)->metatable,
TM_EQ);
break;
}
case 5:{
if(hvalue(t1)==hvalue(t2))return 1;
tm=get_compTM(L,hvalue(t1)->metatable,hvalue(t2)->metatable,TM_EQ);
break;
}
default:return gcvalue(t1)==gcvalue(t2);
}
if(tm==NULL)return 0;
callTMres(L,L->top,tm,t1,t2);
return!l_isfalse(L->top);
}