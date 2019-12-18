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
struct TYPE_3__ {scalar_t__ metatable; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ JSN_DATA ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
create_table(JSN_DATA *data) {
  lua_newtable(data->L);
  if (data->metatable != LUA_NOREF) {
    lua_rawgeti(data->L, LUA_REGISTRYINDEX, data->metatable);
    lua_setmetatable(data->L, -2);
  }
}