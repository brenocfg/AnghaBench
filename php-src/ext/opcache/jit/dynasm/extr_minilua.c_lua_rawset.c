#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  api_checknelems (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index2adr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  luaC_barriert (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  luaH_set (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  luai_apicheck (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ttistable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lua_rawset(lua_State*L,int idx){
StkId t;
api_checknelems(L,2);
t=index2adr(L,idx);
luai_apicheck(L,ttistable(t));
setobj(L,luaH_set(L,hvalue(t),L->top-2),L->top-1);
luaC_barriert(L,hvalue(t),L->top-1);
L->top-=2;
}