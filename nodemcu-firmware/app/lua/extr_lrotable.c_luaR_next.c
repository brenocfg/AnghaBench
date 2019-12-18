#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  ROTable ;

/* Variables and functions */
 int /*<<< orphan*/  luaR_findentry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  luaR_next_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rawtsvalue (int /*<<< orphan*/ *) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ ttisstring (int /*<<< orphan*/ *) ; 

void luaR_next(lua_State *L, ROTable *rotable, TValue *key, TValue *val) {
  unsigned keypos;

  /* Special case: if key is nil, return the first element of the rotable */
  if (ttisnil(key))
    luaR_next_helper(L, rotable, 0, key, val);
  else if (ttisstring(key)) {
    /* Find the previous key again */
    if (ttisstring(key)) {
      luaR_findentry(rotable, rawtsvalue(key), &keypos);
    }
    /* Advance to next key */
    keypos ++;
    luaR_next_helper(L, rotable, keypos, key, val);
  }
}