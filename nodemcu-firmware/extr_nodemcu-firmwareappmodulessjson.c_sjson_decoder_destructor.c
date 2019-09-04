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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  result_ref; int /*<<< orphan*/ * jsn; } ;
typedef  TYPE_1__ JSN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINTF (char*) ; 
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sjson_free_working_data (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int sjson_decoder_destructor(lua_State *L) {
  JSN_DATA *data = (JSN_DATA *)luaL_checkudata(L, 1, "sjson.decoder");

  sjson_free_working_data(L, data);

  data->jsn = NULL;

  luaL_unref(L, LUA_REGISTRYINDEX, data->result_ref);
  data->result_ref = LUA_NOREF;

  DBG_PRINTF("Destructor called\n");

  return 0;
}