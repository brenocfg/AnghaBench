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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {int gcstate; scalar_t__ totalbytes; scalar_t__ estimate; int /*<<< orphan*/  rootgc; int /*<<< orphan*/ * sweepgc; scalar_t__ sweepstrgc; int /*<<< orphan*/  currentwhite; int /*<<< orphan*/ * weak; int /*<<< orphan*/ * grayagain; int /*<<< orphan*/ * gray; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cast_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleartable (int /*<<< orphan*/ *) ; 
 size_t luaC_separateudata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  markmt (TYPE_1__*) ; 
 int /*<<< orphan*/  markobject (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  marktmu (TYPE_1__*) ; 
 int /*<<< orphan*/  otherwhite (TYPE_1__*) ; 
 scalar_t__ propagateall (TYPE_1__*) ; 
 int /*<<< orphan*/  remarkupvals (TYPE_1__*) ; 

__attribute__((used)) static void atomic(lua_State*L){
global_State*g=G(L);
size_t udsize;
remarkupvals(g);
propagateall(g);
g->gray=g->weak;
g->weak=NULL;
markobject(g,L);
markmt(g);
propagateall(g);
g->gray=g->grayagain;
g->grayagain=NULL;
propagateall(g);
udsize=luaC_separateudata(L,0);
marktmu(g);
udsize+=propagateall(g);
cleartable(g->weak);
g->currentwhite=cast_byte(otherwhite(g));
g->sweepstrgc=0;
g->sweepgc=&g->rootgc;
g->gcstate=2;
g->estimate=g->totalbytes-udsize;
}