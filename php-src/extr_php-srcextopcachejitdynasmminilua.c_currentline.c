#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  p; } ;
struct TYPE_4__ {TYPE_1__ l; } ;
typedef  int /*<<< orphan*/  CallInfo ;

/* Variables and functions */
 TYPE_2__* ci_func (int /*<<< orphan*/ *) ; 
 int currentpc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int getline_ (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int currentline(lua_State*L,CallInfo*ci){
int pc=currentpc(L,ci);
if(pc<0)
return-1;
else
return getline_(ci_func(ci)->l.p,pc);
}