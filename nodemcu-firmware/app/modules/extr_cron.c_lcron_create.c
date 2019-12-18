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
struct cronent_desc {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {struct cronent_desc desc; void* cb_ref; } ;
typedef  TYPE_1__ cronent_ud_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int cronent_count ; 
 void** cronent_list ; 
 int /*<<< orphan*/  lcron_parsedesc (int /*<<< orphan*/ *,char*,struct cronent_desc*) ; 
 int /*<<< orphan*/  luaL_checkanyfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 void* os_realloc (void**,int) ; 

__attribute__((used)) static int lcron_create(lua_State *L) {
  // Check arguments
  char *strdesc = (char*)luaL_checkstring(L, 1);
  void *newlist;
  luaL_checkanyfunction(L, 2);
  // Parse description
  struct cronent_desc desc;
  lcron_parsedesc(L, strdesc, &desc);
  // Allocate userdata
  cronent_ud_t *ud = lua_newuserdata(L, sizeof(cronent_ud_t));
  // Set metatable
  luaL_getmetatable(L, "cron.entry");
  lua_setmetatable(L, -2);
  // Set callback
  lua_pushvalue(L, 2);
  ud->cb_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  // Set entry
  ud->desc = desc;
  // Store entry
  newlist = os_realloc(cronent_list, sizeof(int) * (cronent_count + 1));
  if (newlist == NULL) {
    return luaL_error(L, "out of memory");
  }
  lua_pushvalue(L, -1);
  cronent_list = newlist;
  cronent_list[cronent_count++] = luaL_ref(L, LUA_REGISTRYINDEX);
  return 1;
}