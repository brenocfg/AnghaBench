#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_18__ ;
typedef  struct TYPE_21__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_25__ {scalar_t__ top; int base; int /*<<< orphan*/  savedpc; TYPE_1__* ci; } ;
typedef  TYPE_3__ lua_State ;
struct TYPE_28__ {int func; int base; int top; int nresults; scalar_t__ tailcalls; } ;
struct TYPE_27__ {TYPE_4__* p; int /*<<< orphan*/  isC; } ;
struct TYPE_26__ {int maxstacksize; scalar_t__ numparams; int /*<<< orphan*/  code; int /*<<< orphan*/  is_vararg; } ;
struct TYPE_24__ {int (* f ) (TYPE_3__*) ;} ;
struct TYPE_23__ {int /*<<< orphan*/  savedpc; } ;
struct TYPE_22__ {TYPE_5__ l; } ;
struct TYPE_21__ {TYPE_2__ c; } ;
typedef  scalar_t__ StkId ;
typedef  TYPE_4__ Proto ;
typedef  TYPE_5__ LClosure ;
typedef  TYPE_6__ CallInfo ;

/* Variables and functions */
 scalar_t__ adjust_varargs (TYPE_3__*,TYPE_4__*,int) ; 
 int cast_int (scalar_t__) ; 
 TYPE_18__* clvalue (scalar_t__) ; 
 TYPE_16__* curr_func (TYPE_3__*) ; 
 TYPE_6__* inc_ci (TYPE_3__*) ; 
 int /*<<< orphan*/  luaD_checkstack (TYPE_3__*,int) ; 
 int /*<<< orphan*/  luaD_poscall (TYPE_3__*,scalar_t__) ; 
 void* restorestack (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savestack (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  setnilvalue (scalar_t__) ; 
 int stub1 (TYPE_3__*) ; 
 scalar_t__ tryfuncTM (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  ttisfunction (scalar_t__) ; 

__attribute__((used)) static int luaD_precall(lua_State*L,StkId func,int nresults){
LClosure*cl;
ptrdiff_t funcr;
if(!ttisfunction(func))
func=tryfuncTM(L,func);
funcr=savestack(L,func);
cl=&clvalue(func)->l;
L->ci->savedpc=L->savedpc;
if(!cl->isC){
CallInfo*ci;
StkId st,base;
Proto*p=cl->p;
luaD_checkstack(L,p->maxstacksize);
func=restorestack(L,funcr);
if(!p->is_vararg){
base=func+1;
if(L->top>base+p->numparams)
L->top=base+p->numparams;
}
else{
int nargs=cast_int(L->top-func)-1;
base=adjust_varargs(L,p,nargs);
func=restorestack(L,funcr);
}
ci=inc_ci(L);
ci->func=func;
L->base=ci->base=base;
ci->top=L->base+p->maxstacksize;
L->savedpc=p->code;
ci->tailcalls=0;
ci->nresults=nresults;
for(st=L->top;st<ci->top;st++)
setnilvalue(st);
L->top=ci->top;
return 0;
}
else{
CallInfo*ci;
int n;
luaD_checkstack(L,20);
ci=inc_ci(L);
ci->func=restorestack(L,funcr);
L->base=ci->base=ci->func+1;
ci->top=L->top+20;
ci->nresults=nresults;
n=(*curr_func(L)->c.f)(L);
if(n<0)
return 2;
else{
luaD_poscall(L,L->top-n);
return 1;
}
}
}