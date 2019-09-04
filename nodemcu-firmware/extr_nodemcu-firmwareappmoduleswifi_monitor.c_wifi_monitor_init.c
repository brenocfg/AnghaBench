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

/* Variables and functions */
 int /*<<< orphan*/  eventmon_setup () ; 
 int /*<<< orphan*/  luaL_rometatable (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  monitor_task ; 
 scalar_t__ packet_map ; 
 int /*<<< orphan*/  task_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasknumber ; 

int wifi_monitor_init(lua_State *L)
{
  luaL_rometatable(L, "wifi.packet", (void *)packet_map);
  tasknumber = task_get_id(monitor_task);
  eventmon_setup();

#ifdef CHECK_TABLE_IN_ORDER
    // verify that the table is in order
    typekey_t tk;
    tk.key = "";
    tk.frametype = 0;

    int i;
    for (i = 0; i < sizeof(fields) / sizeof(fields[0]); i++) {
      if (comparator(&tk, &fields[i]) >= 0) {
        dbg_printf("Wrong order: %s,%d should be after %s,%d\n", tk.key, tk.frametype, fields[i].name, fields[i].frametype);
      }
      tk.key = fields[i].name;
      tk.frametype = fields[i].frametype;
    }
#endif
  return 0;
}