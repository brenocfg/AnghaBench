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
typedef  int /*<<< orphan*/  ENC_DATA ;

/* Variables and functions */
 scalar_t__ LUA_TNUMBER ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int sjson_encoder_read_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sjson_encoder_read(lua_State *L) {
  ENC_DATA *data = (ENC_DATA *)luaL_checkudata(L, 1, "sjson.encoder");

  int readsize = 1024;
  if (lua_type(L, 2) == LUA_TNUMBER) {
    readsize = lua_tointeger(L, 2);
    if (readsize < 1) {
      readsize = 1;
    }
  }

  return sjson_encoder_read_int(L, data, readsize);
}