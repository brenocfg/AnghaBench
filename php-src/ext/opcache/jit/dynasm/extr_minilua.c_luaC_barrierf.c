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
struct TYPE_5__ {int gcstate; } ;
typedef  TYPE_1__ global_State ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makewhite (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reallymarkobject (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void luaC_barrierf(lua_State*L,GCObject*o,GCObject*v){
global_State*g=G(L);
if(g->gcstate==1)
reallymarkobject(g,v);
else
makewhite(g,o);
}