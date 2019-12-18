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
typedef  scalar_t__ lu_mem ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/ * hash; } ;
struct TYPE_5__ {scalar_t__ totalbytes; scalar_t__ sweepstrgc; int /*<<< orphan*/  estimate; int /*<<< orphan*/  gcstate; TYPE_1__ strt; } ;
typedef  TYPE_2__ global_State ;

/* Variables and functions */
 int /*<<< orphan*/  GCSsweep ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  sweepwholelist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sweepstrstep (global_State *g, lua_State *L) {
  lu_mem old = g->totalbytes;
  sweepwholelist(L, &g->strt.hash[g->sweepstrgc++]);
  if (g->sweepstrgc >= g->strt.size)  /* nothing more to sweep? */
    g->gcstate = GCSsweep;  /* end sweep-string phase */
  lua_assert(old >= g->totalbytes);
  g->estimate -= old - g->totalbytes;
}