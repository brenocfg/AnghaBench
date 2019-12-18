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
struct TYPE_3__ {scalar_t__ start; scalar_t__ end; } ;
typedef  TYPE_1__ buffer_t ;

/* Variables and functions */
 scalar_t__ LUA_TTABLE ; 
 TYPE_1__* checkPipeUD (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pipe__len (lua_State *L) {
  if (lua_type(L, 1) == LUA_TTABLE) {
    lua_pushinteger(L, lua_objlen(L, 1));
  } else {
    buffer_t *ud = checkPipeUD(L, 1);
    lua_pushinteger(L, ud->end - ud->start);
  }
  return 1;
}