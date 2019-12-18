#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cronent_desc {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {struct cronent_desc desc; } ;
typedef  TYPE_1__ cronent_ud_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int cronent_count ; 
 int /*<<< orphan*/ * cronent_list ; 
 size_t lcron_findindex (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lcron_parsedesc (int /*<<< orphan*/ *,char*,struct cronent_desc*) ; 
 scalar_t__ luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* os_realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lcron_schedule(lua_State *L) {
  cronent_ud_t *ud = luaL_checkudata(L, 1, "cron.entry");
  char *strdesc = (char*)luaL_checkstring(L, 2);
  struct cronent_desc desc;
  lcron_parsedesc(L, strdesc, &desc);
  ud->desc = desc;
  size_t i = lcron_findindex(L, ud);
  if (i == -1) {
    void *newlist;
    newlist = os_realloc(cronent_list, sizeof(int) * (cronent_count + 1));
    if (newlist == NULL) {
      return luaL_error(L, "out of memory");
    }
    cronent_list = newlist;
    lua_pushvalue(L, 1);
    cronent_list[cronent_count++] = lua_ref(L, LUA_REGISTRYINDEX);
  }
  return 0;
}