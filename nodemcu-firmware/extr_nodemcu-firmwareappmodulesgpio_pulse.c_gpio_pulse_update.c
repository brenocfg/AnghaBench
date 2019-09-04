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
struct TYPE_3__ {int entry_count; int /*<<< orphan*/ * entry; } ;
typedef  TYPE_1__ pulse_t ;
typedef  int /*<<< orphan*/  pulse_entry_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  ETS_FRC1_INTR_DISABLE () ; 
 int /*<<< orphan*/  ETS_FRC1_INTR_ENABLE () ; 
 int /*<<< orphan*/  fill_entry_from_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gpio_pulse_update(lua_State *L) {
  pulse_t *pulser = luaL_checkudata(L, 1, "gpio.pulse");
  int entry_pos = luaL_checkinteger(L, 2);

  if (entry_pos < 1 || entry_pos > pulser->entry_count) {
    return luaL_error(L, "entry number must be in range 1 .. %d", pulser->entry_count);
  }

  pulse_entry_t *entry = pulser->entry + entry_pos - 1;

  pulse_entry_t new_entry = *entry;

  lua_pushvalue(L, 3);

  fill_entry_from_table(L, &new_entry);

  // Now do the update
  ETS_FRC1_INTR_DISABLE();
  *entry = new_entry;
  ETS_FRC1_INTR_ENABLE();

  return 0;
}