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
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sjson_encoder (int /*<<< orphan*/ *) ; 
 int sjson_encoder_read_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sjson_encode(lua_State *L) {
  sjson_encoder(L);

  ENC_DATA *data = (ENC_DATA *)luaL_checkudata(L, -1, "sjson.encoder");

  int rc = sjson_encoder_read_int(L, data, 1000000);

  lua_remove(L, -(rc + 1));

  return rc;
}