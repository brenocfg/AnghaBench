#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int const uint8 ;
struct TYPE_4__ {size_t Subtype; } ;
struct TYPE_5__ {TYPE_1__ framectrl; } ;
typedef  TYPE_2__ management_request_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int const*,int const) ; 
 int* variable_start ; 

__attribute__((used)) static bool push_field_value_int(lua_State *L, management_request_t *mgt,
    const uint8 *packet_end, int field) {

  int varstart = variable_start[mgt->framectrl.Subtype];
  if (varstart >= 0) {
    uint8 *var = (uint8 *) (mgt + 1) + varstart;

    while (var + 2 <= packet_end && var + 2 + var[1] <= packet_end) {
      if (*var == field) {
        lua_pushlstring(L, var + 2, var[1]);
        return true;
      }
      var += var[1] + 2;
    }
  }

  return false;
}