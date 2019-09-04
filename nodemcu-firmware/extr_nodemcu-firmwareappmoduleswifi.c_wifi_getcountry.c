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
struct TYPE_3__ {char* cc; scalar_t__ policy; scalar_t__ nchan; scalar_t__ schan; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ wifi_country_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 scalar_t__ wifi_get_country (TYPE_1__*) ; 

__attribute__((used)) static int wifi_getcountry( lua_State* L ){

  wifi_country_t cfg = {0};


  if(wifi_get_country(&cfg)){
    lua_newtable(L);

    lua_pushstring(L, "country");
    lua_pushstring(L, cfg.cc);
    lua_rawset(L, -3);

    lua_pushstring(L, "start_ch");
    lua_pushnumber(L, cfg.schan);
    lua_rawset(L, -3);

    lua_pushstring(L, "end_ch");
    lua_pushnumber(L, (cfg.schan + cfg.nchan)-1);
    lua_rawset(L, -3);

    lua_pushstring(L, "policy");
    lua_pushnumber(L, cfg.policy);
    lua_rawset(L, -3);

    return 1;
  }
  else{
    return luaL_error(L, "Unable to get country info");
  }
}