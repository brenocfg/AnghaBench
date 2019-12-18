#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  sizearray; int /*<<< orphan*/ * array; int /*<<< orphan*/ * node; } ;
typedef  TYPE_1__ Table ;

/* Variables and functions */
 int /*<<< orphan*/  Node ; 
 int /*<<< orphan*/  TValue ; 
 int /*<<< orphan*/  dummynode_ ; 
 int /*<<< orphan*/  luaM_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  luaM_freearray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizenode (TYPE_1__*) ; 

__attribute__((used)) static void luaH_free(lua_State*L,Table*t){
if(t->node!=(&dummynode_))
luaM_freearray(L,t->node,sizenode(t),Node);
luaM_freearray(L,t->array,t->sizearray,TValue);
luaM_free(L,t);
}