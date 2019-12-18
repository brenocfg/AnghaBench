#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_13__ {int /*<<< orphan*/ ** mt; } ;
struct TYPE_12__ {int /*<<< orphan*/ * metatable; } ;
struct TYPE_11__ {int /*<<< orphan*/ * metatable; } ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 TYPE_8__* G (TYPE_1__*) ; 
 int /*<<< orphan*/  api_incr_top (TYPE_1__*) ; 
 TYPE_6__* hvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * index2adr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sethvalue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t ttype (int /*<<< orphan*/  const*) ; 
 TYPE_2__* uvalue (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int lua_getmetatable(lua_State*L,int objindex){
const TValue*obj;
Table*mt=NULL;
int res;
obj=index2adr(L,objindex);
switch(ttype(obj)){
case 5:
mt=hvalue(obj)->metatable;
break;
case 7:
mt=uvalue(obj)->metatable;
break;
default:
mt=G(L)->mt[ttype(obj)];
break;
}
if(mt==NULL)
res=0;
else{
sethvalue(L,L->top,mt);
api_incr_top(L);
res=1;
}
return res;
}