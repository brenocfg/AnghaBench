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
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ output_redir_ref ; 
 scalar_t__ serial_debug ; 
 int /*<<< orphan*/  uart0_sendStr (char const*) ; 

void output_redirect(const char *str) {
  lua_State *L = lua_getstate();
  // if(strlen(str)>=TX_BUFF_SIZE){
  //   NODE_ERR("output too long.\n");
  //   return;
  // }

  if (output_redir_ref == LUA_NOREF) {
    uart0_sendStr(str);
    return;
  }

  if (serial_debug != 0) {
    uart0_sendStr(str);
  }

  lua_rawgeti(L, LUA_REGISTRYINDEX, output_redir_ref);
  lua_pushstring(L, str);
  lua_call(L, 1, 0);   // this call back function should never user output.
}