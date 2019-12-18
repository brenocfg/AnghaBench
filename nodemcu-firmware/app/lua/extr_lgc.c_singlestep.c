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
typedef  int lu_mem ;
typedef  int l_mem ;
struct TYPE_5__ {int gcstate; int totalbytes; int estimate; int /*<<< orphan*/  gcdept; int /*<<< orphan*/  tmudata; int /*<<< orphan*/ ** sweepgc; int /*<<< orphan*/  gray; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int GCFINALIZECOST ; 
 int GCSWEEPCOST ; 
 int GCSWEEPMAX ; 
#define  GCSfinalize 132 
#define  GCSpause 131 
#define  GCSpropagate 130 
#define  GCSsweep 129 
#define  GCSsweepstring 128 
 int /*<<< orphan*/  GCTM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkSizes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  markroot (int /*<<< orphan*/ *) ; 
 int propagatemark (TYPE_1__*) ; 
 int /*<<< orphan*/ ** sweeplist (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  sweepstrstep (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static l_mem singlestep (lua_State *L) {
  global_State *g = G(L);
  /*lua_checkmemory(L);*/
  switch (g->gcstate) {
    case GCSpause: {
      markroot(L);  /* start a new collection */
      return 0;
    }
    case GCSpropagate: {
      if (g->gray)
        return propagatemark(g);
      else {  /* no more `gray' objects */
        atomic(L);  /* finish mark phase */
        return 0;
      }
    }
    case GCSsweepstring: {
      sweepstrstep(g, L);
      return GCSWEEPCOST;
    }
    case GCSsweep: {
      lu_mem old = g->totalbytes;
      g->sweepgc = sweeplist(L, g->sweepgc, GCSWEEPMAX);
      if (*g->sweepgc == NULL) {  /* nothing more to sweep? */
        checkSizes(L);
        g->gcstate = GCSfinalize;  /* end sweep phase */
      }
      lua_assert(old >= g->totalbytes);
      g->estimate -= old - g->totalbytes;
      return GCSWEEPMAX*GCSWEEPCOST;
    }
    case GCSfinalize: {
      if (g->tmudata) {
        GCTM(L);
        if (g->estimate > GCFINALIZECOST)
          g->estimate -= GCFINALIZECOST;
        return GCFINALIZECOST;
      }
      else {
        g->gcstate = GCSpause;  /* end collection */
        g->gcdept = 0;
        return 0;
      }
    }
    default: lua_assert(0); return 0;
  }
}