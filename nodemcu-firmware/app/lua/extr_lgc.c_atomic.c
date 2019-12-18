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
struct TYPE_9__ {scalar_t__ totalbytes; scalar_t__ estimate; int /*<<< orphan*/  gcstate; int /*<<< orphan*/  rootgc; int /*<<< orphan*/ * sweepgc; scalar_t__ sweepstrgc; int /*<<< orphan*/  currentwhite; int /*<<< orphan*/ * weak; int /*<<< orphan*/ * grayagain; int /*<<< orphan*/ * gray; int /*<<< orphan*/  mainthread; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GCSsweepstring ; 
 int /*<<< orphan*/  cast_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleartable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iswhite (int /*<<< orphan*/ ) ; 
 size_t luaC_separateudata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  markmt (TYPE_1__*) ; 
 int /*<<< orphan*/  markobject (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  marktmu (TYPE_1__*) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otherwhite (TYPE_1__*) ; 
 scalar_t__ propagateall (TYPE_1__*) ; 
 int /*<<< orphan*/  remarkupvals (TYPE_1__*) ; 

__attribute__((used)) static void atomic (lua_State *L) {
  global_State *g = G(L);
  size_t udsize;  /* total size of userdata to be finalized */
  /* remark occasional upvalues of (maybe) dead threads */
  remarkupvals(g);
  /* traverse objects caucht by write barrier and by 'remarkupvals' */
  propagateall(g);
  /* remark weak tables */
  g->gray = g->weak;
  g->weak = NULL;
  lua_assert(!iswhite(obj2gco(g->mainthread)));
  markobject(g, L);  /* mark running thread */
  markmt(g);  /* mark basic metatables (again) */
  propagateall(g);
  /* remark gray again */
  g->gray = g->grayagain;
  g->grayagain = NULL;
  propagateall(g);
  udsize = luaC_separateudata(L, 0);  /* separate userdata to be finalized */
  marktmu(g);  /* mark `preserved' userdata */
  udsize += propagateall(g);  /* remark, to propagate `preserveness' */
  cleartable(g->weak);  /* remove collected objects from weak tables */
  /* flip current white */
  g->currentwhite = cast_byte(otherwhite(g));
  g->sweepstrgc = 0;
  g->sweepgc = &g->rootgc;
  g->gcstate = GCSsweepstring;
  g->estimate = g->totalbytes - udsize;  /* first estimate */
}