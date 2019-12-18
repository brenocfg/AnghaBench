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
struct TYPE_6__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  hvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index2adr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  luaH_get (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  luai_apicheck (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttistable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lua_rawget(lua_State*L,int idx){
StkId t;
t=index2adr(L,idx);
luai_apicheck(L,ttistable(t));
setobj(L,L->top-1,luaH_get(hvalue(t),L->top-1));
}