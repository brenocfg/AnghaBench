#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ci; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  CallInfo ;

/* Variables and functions */
 int LUA_IDSIZE ; 
 int currentline (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* getluaproto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getstr (int /*<<< orphan*/ ) ; 
 scalar_t__ isLua (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaO_chunkid (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaO_pushfstring (TYPE_1__*,char*,char*,int,char const*) ; 

__attribute__((used)) static void addinfo (lua_State *L, const char *msg) {
  CallInfo *ci = L->ci;
  if (isLua(ci)) {  /* is Lua code? */
    char buff[LUA_IDSIZE];  /* add file:line information */
    int line = currentline(L, ci);
    luaO_chunkid(buff, getstr(getluaproto(ci)->source), LUA_IDSIZE);
    luaO_pushfstring(L, "%s:%d: %s", buff, line, msg);
  }
}