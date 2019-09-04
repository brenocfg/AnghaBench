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
struct TYPE_3__ {int result_ref; int /*<<< orphan*/  complete; } ;
typedef  TYPE_1__ JSN_DATA ;

/* Variables and functions */
 int LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sjson_decoder_result_int(lua_State *L, JSN_DATA *data) {
  if (!data->complete) {
    luaL_error(L, "decode not complete");
  }

  lua_rawgeti(L, LUA_REGISTRYINDEX, data->result_ref);
  lua_rawgeti(L, -1, 1);
  lua_remove(L, -2);

  return 1;
}