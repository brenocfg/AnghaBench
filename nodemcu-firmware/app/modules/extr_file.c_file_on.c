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
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int /*<<< orphan*/  LUA_TLIGHTFUNCTION ; 
 int /*<<< orphan*/ * file_rtc_cb ; 
 int luaL_checkoption (int /*<<< orphan*/ *,int,char*,char const* const*) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtc_cb_ref ; 
 int /*<<< orphan*/  vfs_register_rtc_cb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int file_on(lua_State *L)
{
  enum events{
    ON_RTC = 0
  };
  const char *const eventnames[] = {"rtc", NULL};

  int event = luaL_checkoption(L, 1, "rtc", eventnames);

  switch (event) {
  case ON_RTC:
    luaL_unref(L, LUA_REGISTRYINDEX, rtc_cb_ref);

    if ((lua_type(L, 2) == LUA_TFUNCTION) ||
        (lua_type(L, 2) == LUA_TLIGHTFUNCTION)) {
      lua_pushvalue(L, 2);  // copy argument (func) to the top of stack
      rtc_cb_ref = luaL_ref(L, LUA_REGISTRYINDEX);
      vfs_register_rtc_cb(file_rtc_cb);
    } else {
      rtc_cb_ref = LUA_NOREF;
      vfs_register_rtc_cb(NULL);
    }
    break;
  default:
    break;
  }

  return 0;
}