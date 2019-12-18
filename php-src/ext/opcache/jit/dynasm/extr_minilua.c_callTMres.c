#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_8__ {int /*<<< orphan*/  const* top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  const* StkId ;

/* Variables and functions */
 int /*<<< orphan*/  luaD_call (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  luaD_checkstack (TYPE_1__*,int) ; 
 int /*<<< orphan*/  const* restorestack (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savestack (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setobj (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void callTMres(lua_State*L,StkId res,const TValue*f,
const TValue*p1,const TValue*p2){
ptrdiff_t result=savestack(L,res);
setobj(L,L->top,f);
setobj(L,L->top+1,p1);
setobj(L,L->top+2,p2);
luaD_checkstack(L,3);
L->top+=3;
luaD_call(L,L->top-3,1);
res=restorestack(L,result);
L->top--;
setobj(L,res,L->top);
}