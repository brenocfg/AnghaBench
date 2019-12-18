#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {scalar_t__ gcstate; } ;
typedef  TYPE_2__ global_State ;
struct TYPE_9__ {int /*<<< orphan*/  marked; } ;
struct TYPE_11__ {TYPE_1__ gch; } ;
typedef  TYPE_3__ GCObject ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 scalar_t__ GCSpropagate ; 
 int /*<<< orphan*/  luaC_white (TYPE_2__*) ; 
 int /*<<< orphan*/  reallymarkobject (TYPE_2__*,TYPE_3__*) ; 

void luaC_marknew (lua_State *L, GCObject *o) {
  global_State *g = G(L);
  o->gch.marked = luaC_white(g);
  if (g->gcstate == GCSpropagate)
    reallymarkobject(g, o);  /* mark new objects as gray during propagate state. */
}