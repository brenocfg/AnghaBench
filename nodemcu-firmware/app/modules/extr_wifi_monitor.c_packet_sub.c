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
typedef  int ptrdiff_t ;
struct TYPE_3__ {int buf; } ;
typedef  TYPE_1__ packet_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int,int) ; 
 int posrelat (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int packet_sub(lua_State *L, int buf_offset, int buf_length) {
  packet_t *packet = luaL_checkudata(L, 1, "wifi.packet");

  ptrdiff_t start = posrelat(luaL_checkinteger(L, 2), buf_length);
  ptrdiff_t end = posrelat(luaL_optinteger(L, 3, -1), buf_length);

  if (start < 1) start = 1;
  if (end > buf_length) end = buf_length;
  if (start <= end) {
    lua_pushlstring(L, packet->buf+start-1 + buf_offset, end-start+1);
  } else {
    lua_pushliteral(L, "");
  }

  return 1;
}