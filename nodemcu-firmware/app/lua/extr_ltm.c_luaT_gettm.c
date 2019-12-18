#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TString ;
typedef  unsigned int TMS ;

/* Variables and functions */
 unsigned int TM_EQ ; 
 int /*<<< orphan*/  cast_byte (unsigned int) ; 
 int /*<<< orphan*/ * luaH_getstr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaH_getstr_ro (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ luaR_isrotable (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/  const*) ; 

const TValue *luaT_gettm (Table *events, TMS event, TString *ename) {
  const TValue *tm;
  lua_assert(event <= TM_EQ);

  if (luaR_isrotable(events)) {
    tm =  luaH_getstr_ro(events, ename);
    if (ttisnil(tm)) {  /* no tag method? */
      return NULL;
    }
  } else {
    tm = luaH_getstr(events, ename);
    if (ttisnil(tm)) {  /* no tag method? */
      events->flags |= cast_byte(1u<<event);  /* cache this fact */
      return NULL;
    }
  }
  return tm;
}