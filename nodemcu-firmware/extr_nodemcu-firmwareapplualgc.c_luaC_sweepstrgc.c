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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {scalar_t__ gcstate; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 scalar_t__ GCSsweepstring ; 
 int /*<<< orphan*/  sweepstrstep (TYPE_1__*,int /*<<< orphan*/ *) ; 

int luaC_sweepstrgc (lua_State *L) {
  global_State *g = G(L);
  if (g->gcstate == GCSsweepstring) {
    sweepstrstep(g, L);
    return (g->gcstate == GCSsweepstring) ? 1 : 0;
  }
  return 0;
}