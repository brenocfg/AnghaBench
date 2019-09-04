#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lu_mem ;
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_12__ {int /*<<< orphan*/  openupval; } ;
struct TYPE_11__ {scalar_t__ tt; int marked; TYPE_1__* next; } ;
struct TYPE_10__ {TYPE_6__ gch; } ;
typedef  TYPE_1__ GCObject ;

/* Variables and functions */
 int /*<<< orphan*/  FIXEDBIT ; 
 int /*<<< orphan*/ * G (int /*<<< orphan*/ *) ; 
 scalar_t__ LUA_TTHREAD ; 
 int /*<<< orphan*/  SFIXEDBIT ; 
 int WHITEBITS ; 
 int bitmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeobj (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_7__* gco2th (TYPE_1__*) ; 
 int /*<<< orphan*/  isLFSobject (TYPE_6__*) ; 
 scalar_t__ isdead (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  makewhite (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int otherwhite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sweepwholelist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ testbit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GCObject **sweeplist (lua_State *L, GCObject **p, lu_mem count) {
  GCObject *curr;
  global_State *g = G(L);
  int deadmask = otherwhite(g);
  while ((curr = *p) != NULL && count-- > 0) {
    lua_assert(!isLFSobject(&(curr->gch)) || curr->gch.tt == LUA_TTHREAD);
    if (curr->gch.tt == LUA_TTHREAD)  /* sweep open upvalues of each thread */
      sweepwholelist(L, &gco2th(curr)->openupval);
    if ((curr->gch.marked ^ WHITEBITS) & deadmask) {  /* not dead? */
      lua_assert(!isdead(g, curr) || testbit(curr->gch.marked, FIXEDBIT));
      makewhite(g, curr);  /* make it white (for next cycle) */
      p = &curr->gch.next;
    }
    else {  /* must erase `curr' */
      lua_assert(isdead(g, curr) || deadmask == bitmask(SFIXEDBIT));
      *p = curr->gch.next;
      freeobj(L, curr);
    }
  }
  return p;
}