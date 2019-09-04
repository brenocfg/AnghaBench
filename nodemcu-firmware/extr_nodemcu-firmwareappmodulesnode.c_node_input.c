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
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ lua_put_line (char const*,size_t) ; 
 int /*<<< orphan*/  user_process_input (int) ; 

__attribute__((used)) static int node_input( lua_State* L ) {
  size_t l = 0;
  const char *s = luaL_checklstring(L, 1, &l);
  if (lua_put_line(s, l)) {
    NODE_DBG("Result (if any):\n");
    user_process_input(true);
  }
  return 0;
}