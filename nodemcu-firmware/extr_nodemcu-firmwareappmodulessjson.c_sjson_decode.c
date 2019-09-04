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
 int /*<<< orphan*/  luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int sjson_decoder_int (int /*<<< orphan*/ *,int) ; 
 int sjson_decoder_write_int (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int sjson_decode(lua_State *L) {
  int push_count = sjson_decoder_int(L, 2);
  if (push_count != 1) {
    luaL_error(L, "Internal error in sjson.deocder");
  }

  luaL_checkudata(L, -1, "sjson.decoder");

  push_count = sjson_decoder_write_int(L, -1, 1);

  if (push_count != 1) {
    luaL_error(L, "Incomplete JSON object passed to sjson.decode");
  }

  // Now we have two items on the stack -- the udata and the result
  lua_remove(L, -2);

  return 1;
}