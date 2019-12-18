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
struct TYPE_3__ {int* cc; int schan; int nchan; int policy; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ wifi_country_t ;
typedef  int uint8 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int WIFI_COUNTRY_POLICY_AUTO ; 
 int WIFI_COUNTRY_POLICY_MANUAL ; 
 int /*<<< orphan*/  WIFI_DBG (char*,int*,int,int,int) ; 
 scalar_t__ isalpha (char const) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int*,char const*,size_t) ; 
 int wifi_set_country (TYPE_1__*) ; 

__attribute__((used)) static int wifi_setcountry( lua_State* L ){
  size_t len;
  uint8 start_ch;
  uint8 end_ch;
  wifi_country_t cfg = {0};

  if(lua_istable(L, 1)){
    lua_getfield(L, 1, "country");
    if (!lua_isnil(L, -1)){
      if( lua_isstring(L, -1) ){
        const char *country_code = luaL_checklstring( L, -1, &len );
        luaL_argcheck(L, (len==2 && isalpha(country_code[0]) && isalpha(country_code[1])), 1, "country: country code must be 2 chars");
        memcpy(cfg.cc, country_code, len);
        if(cfg.cc[0] >= 0x61) cfg.cc[0]=cfg.cc[0]-32; //if lowercase change to uppercase
        if(cfg.cc[1] >= 0x61) cfg.cc[1]=cfg.cc[1]-32; //if lowercase change to uppercase
      }
      else
        return luaL_argerror( L, 1, "country: must be string" );
    }
    else{
      cfg.cc[0]='C';
      cfg.cc[1]='N';
      cfg.cc[2]=0x00;
    }
    lua_pop(L, 1);

    lua_getfield(L, 1, "start_ch");
    if (!lua_isnil(L, -1)){
      if(lua_isnumber(L, -1)){
        start_ch = (uint8)luaL_checknumber(L, -1);
        luaL_argcheck(L, (start_ch >= 1 && start_ch <= 14), 1, "start_ch: Range:1-14");
        cfg.schan = start_ch;
      }
      else
        luaL_argerror(L, 1, "start_ch: must be a number");
    }
    else
      cfg.schan = 1;

    lua_pop(L, 1);

    lua_getfield(L, 1, "end_ch");
    if (!lua_isnil(L, -1)){
      if(lua_isnumber(L, -1)){
        end_ch = (uint8)luaL_checknumber(L, -1);
        luaL_argcheck(L, (end_ch >= 1 && end_ch <= 14), 1, "end_ch: Range:1-14");
        luaL_argcheck(L, (end_ch >= cfg.schan), 1, "end_ch: can't be less than start_ch");
        cfg.nchan = (end_ch-cfg.schan)+1; //cfg.nchan must equal total number of channels
      }
      else
        luaL_argerror(L, 1, "end_ch: must be a number");
    }
    else
      cfg.nchan = (13-cfg.schan)+1;
    lua_pop(L, 1);

    lua_getfield(L, 1, "policy");
    if (!lua_isnil(L, -1)){
      if(lua_isnumber(L, -1)){
        uint8 policy = (uint8)luaL_checknumber(L, -1);
        luaL_argcheck(L, (policy == WIFI_COUNTRY_POLICY_AUTO || policy == WIFI_COUNTRY_POLICY_MANUAL), 1, "policy: must be 0 or 1");
        cfg.policy = policy;
      }
      else
        luaL_argerror(L, 1, "policy: must be a number");
    }
    else
      cfg.policy = WIFI_COUNTRY_POLICY_AUTO;
    lua_pop(L, 1);

    lua_pop(L, 1); //pop table from stack

    bool retval = wifi_set_country(&cfg);
    WIFI_DBG("\n country_cfg:\tcc:\"%s\"\tschan:%d\tnchan:%d\tpolicy:%d\n", cfg.cc, cfg.schan, cfg.nchan, cfg.policy);

    if (retval==1)
      lua_pushboolean(L, true);
    else
      return luaL_error(L, "Unable to set country info");
  }
  else
    return luaL_argerror(L, 1, "Table not found!");
  return 1;
}