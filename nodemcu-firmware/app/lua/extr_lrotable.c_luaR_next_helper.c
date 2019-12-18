#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  value; scalar_t__ key; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ ROTable ;

/* Variables and functions */
 int /*<<< orphan*/  luaS_new (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setnilvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setobj2s (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void luaR_next_helper(lua_State *L, ROTable *pentries, int pos,
                             TValue *key, TValue *val) {
  if (pentries[pos].key) {
    /* Found an entry */
    setsvalue(L, key, luaS_new(L, pentries[pos].key));
    setobj2s(L, val, &pentries[pos].value);
  } else {
    setnilvalue(key);
    setnilvalue(val);
  }
}