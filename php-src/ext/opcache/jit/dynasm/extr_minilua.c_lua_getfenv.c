#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_11__ {int /*<<< orphan*/  env; } ;
struct TYPE_14__ {TYPE_1__ c; } ;
struct TYPE_13__ {int /*<<< orphan*/  env; } ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  api_checkvalidindex (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  api_incr_top (TYPE_2__*) ; 
 TYPE_8__* clvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index2adr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sethvalue (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thvalue (int /*<<< orphan*/ ) ; 
 int ttype (int /*<<< orphan*/ ) ; 
 TYPE_3__* uvalue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lua_getfenv(lua_State*L,int idx){
StkId o;
o=index2adr(L,idx);
api_checkvalidindex(L,o);
switch(ttype(o)){
case 6:
sethvalue(L,L->top,clvalue(o)->c.env);
break;
case 7:
sethvalue(L,L->top,uvalue(o)->env);
break;
case 8:
setobj(L,L->top,gt(thvalue(o)));
break;
default:
setnilvalue(L->top);
break;
}
api_incr_top(L);
}