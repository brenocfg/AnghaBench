#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int size; int /*<<< orphan*/ * hash; } ;
struct TYPE_5__ {int currentwhite; TYPE_1__ strt; int /*<<< orphan*/  rootgc; } ;
typedef  TYPE_2__ global_State ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 int bit2mask (int /*<<< orphan*/ ,int) ; 
 int bitmask (int) ; 
 int /*<<< orphan*/  sweepwholelist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void luaC_freeall(lua_State*L){
global_State*g=G(L);
int i;
g->currentwhite=bit2mask(0,1)|bitmask(6);
sweepwholelist(L,&g->rootgc);
for(i=0;i<g->strt.size;i++)
sweepwholelist(L,&g->strt.hash[i]);
}