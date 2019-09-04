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
struct TYPE_3__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ packet_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int packet_byte(lua_State *L, int buf_offset, int buf_length) {
  packet_t *packet = luaL_checkudata(L, 1, "wifi.packet");

  int offset = luaL_checkinteger(L, 2);

  if (offset < 1 || offset > buf_length) {
    return 0;
  }

  lua_pushinteger(L, packet->buf[offset - 1 + buf_offset]);

  return 1;
}