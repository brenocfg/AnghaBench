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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 void* RTC_DEFAULT_TAGCOUNT ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_isnone (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 void* lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtc_fifo_prepare (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  rtc_fifo_put_loc (int,int,void*) ; 

__attribute__((used)) static int rtcfifo_prepare (lua_State *L)
{
  uint32_t sensor_count = RTC_DEFAULT_TAGCOUNT;
  uint32_t interval_us = 0;
  int first = -1, last = -1;

  if (lua_istable (L, 1))
  {
#ifdef LUA_USE_MODULES_RTCTIME
    lua_getfield (L, 1, "interval_us");
    if (lua_isnumber (L, -1))
      interval_us = lua_tonumber (L, -1);
    lua_pop (L, 1);
#endif

    lua_getfield (L, 1, "sensor_count");
    if (lua_isnumber (L, -1))
      sensor_count = lua_tonumber (L, -1);
    lua_pop (L, 1);

    lua_getfield (L, 1, "storage_begin");
    if (lua_isnumber (L, -1))
      first = lua_tonumber (L, -1);
    lua_pop (L, 1);
    lua_getfield (L, 1, "storage_end");
    if (lua_isnumber (L, -1))
      last = lua_tonumber (L, -1);
    lua_pop (L, 1);
  }
  else if (!lua_isnone (L, 1))
    return luaL_error (L, "expected table as arg #1");

  rtc_fifo_prepare (0, interval_us, sensor_count);

  if (first != -1 && last != -1)
    rtc_fifo_put_loc (first, last, sensor_count);

  return 0;
}