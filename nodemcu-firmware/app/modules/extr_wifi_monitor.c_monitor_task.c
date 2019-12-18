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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ packet_t ;
typedef  scalar_t__ os_param_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ recv_cb ; 

__attribute__((used)) static void monitor_task(os_param_t param, uint8_t prio)
{
  packet_t *input = (packet_t *) param;
  (void) prio;

  lua_State *L = lua_getstate();

  if (recv_cb != LUA_NOREF) {
    lua_rawgeti(L, LUA_REGISTRYINDEX, recv_cb);

    packet_t *packet = (packet_t *) lua_newuserdata(L, input->len + sizeof(packet_t));
    packet->len = input->len;
    memcpy(packet->buf, input->buf, input->len);
    luaL_getmetatable(L, "wifi.packet");
    lua_setmetatable(L, -2);

    free(input);

    lua_call(L, 1, 0);
  } else {
    free(input);
  }
}