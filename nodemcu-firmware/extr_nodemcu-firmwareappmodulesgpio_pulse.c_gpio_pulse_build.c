#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t entry_count; TYPE_2__* entry; } ;
typedef  TYPE_1__ pulse_t ;
struct TYPE_6__ {int delay_min; int delay_max; } ;
typedef  TYPE_2__ pulse_entry_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  fill_entry_from_table (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 size_t luaL_getn (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int gpio_pulse_build(lua_State *L) {
  // Take a table argument
  luaL_checktype(L, 1, LUA_TTABLE);

  // First figure out how big we need the block to be
  size_t size = luaL_getn(L, 1);

  if (size > 100) {
    return luaL_error(L, "table is too large: %d entries is more than 100", size);
  }

  size_t memsize = sizeof(pulse_t) + size * sizeof(pulse_entry_t);
  pulse_t *pulser = (pulse_t *) lua_newuserdata(L, memsize);
  memset(pulser, 0, memsize);
  //
  // Associate its metatable
  luaL_getmetatable(L, "gpio.pulse");
  lua_setmetatable(L, -2);

  pulser->entry = (pulse_entry_t *) (pulser + 1);
  pulser->entry_count = size;

  size_t i;
  for (i = 0; i < size; i++) {
    pulse_entry_t *entry = pulser->entry + i;

    entry->delay_min = -1;
    entry->delay_max = -1;

    lua_rawgeti(L, 1, i + 1);

    fill_entry_from_table(L, entry);
  }

  return 1;
}