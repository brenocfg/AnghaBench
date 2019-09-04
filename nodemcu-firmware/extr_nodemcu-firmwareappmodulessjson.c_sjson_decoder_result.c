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
typedef  int /*<<< orphan*/  JSN_DATA ;

/* Variables and functions */
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int sjson_decoder_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sjson_decoder_result(lua_State *L) {
  JSN_DATA *data = (JSN_DATA *)luaL_checkudata(L, 1, "sjson.decoder");

  return sjson_decoder_result_int(L, data);
}