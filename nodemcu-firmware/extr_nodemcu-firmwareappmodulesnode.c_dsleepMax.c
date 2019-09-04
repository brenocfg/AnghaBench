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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ system_rtc_clock_cali_proc () ; 

__attribute__((used)) static int dsleepMax( lua_State *L ) {
  lua_pushnumber(L, (uint64_t)system_rtc_clock_cali_proc()*(0x80000000-1)/(0x1000));
  return 1;
}