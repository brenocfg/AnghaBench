#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ntp_err_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {scalar_t__ err_cb_ref; } ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 scalar_t__ LUA_REFNIL ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sntp_dbg (char*) ; 
 TYPE_1__* state ; 

__attribute__((used)) static void handle_error (lua_State *L, ntp_err_t err, const char *msg)
{
  sntp_dbg("sntp: handle_error\n");
  if (state->err_cb_ref != LUA_NOREF && state->err_cb_ref != LUA_REFNIL)
  {
    lua_rawgeti (L, LUA_REGISTRYINDEX, state->err_cb_ref);
    lua_pushinteger (L, err);
    lua_pushstring (L, msg);
    cleanup (L);
    lua_call (L, 2, 0);
  }
  else
    cleanup (L);
}