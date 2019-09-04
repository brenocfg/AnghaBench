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
struct TYPE_9__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  TString ;

/* Variables and functions */
 void* fromFashAddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  lua_isnil (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_pop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_pushnil (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_rawget (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_tointeger (TYPE_1__*,int) ; 
 int /*<<< orphan*/  setsvalue (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *resolveTString(lua_State* L, TString *s) {
  if (!s)
    return NULL;
  lua_pushnil(L);
  setsvalue(L, L->top-1, s);
  lua_rawget(L, -2);
  lua_assert(!lua_isnil(L, -1));
  void *ts = fromFashAddr(lua_tointeger(L, -1));
  lua_pop(L, 1);
  return ts;
}