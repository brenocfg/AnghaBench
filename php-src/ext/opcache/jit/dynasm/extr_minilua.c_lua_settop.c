#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int stack_last; int base; scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luai_apicheck (TYPE_1__*,int) ; 
 int /*<<< orphan*/  setnilvalue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lua_settop(lua_State*L,int idx){
if(idx>=0){
luai_apicheck(L,idx<=L->stack_last-L->base);
while(L->top<L->base+idx)
setnilvalue(L->top++);
L->top=L->base+idx;
}
else{
luai_apicheck(L,-(idx+1)<=(L->top-L->base));
L->top+=idx+1;
}
}