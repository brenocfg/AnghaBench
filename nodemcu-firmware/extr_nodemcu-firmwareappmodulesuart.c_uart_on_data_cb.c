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
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  run_input ; 
 scalar_t__ uart_receive_rf ; 

bool uart_on_data_cb(const char *buf, size_t len){
  if(!buf || len==0)
    return false;
  if(uart_receive_rf == LUA_NOREF)
    return false;
  lua_State *L = lua_getstate();
  if(!L)
    return false;
  lua_rawgeti(L, LUA_REGISTRYINDEX, uart_receive_rf);
  lua_pushlstring(L, buf, len);
  lua_call(L, 1, 0);
  return !run_input;
}