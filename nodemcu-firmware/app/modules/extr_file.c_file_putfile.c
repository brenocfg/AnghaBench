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
 int /*<<< orphan*/  file_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int file_putfile( lua_State* L )
{
  // Warning this code C calls other file_* routines to avoid duplication code.  These
  // use Lua stack addressing of arguments, so this does Lua stack maniplation to
  // align these
  int ret_cnt = 0;
  lua_settop(L, 2);
  lua_pushvalue(L, 2); //dup contents onto the ToS [3]
  lua_pushliteral(L, "w+");
  lua_replace(L, 2);
  // Stack [1] = filename; [2] "w+" [3] contents;
  file_open(L);
  // Stack [1] = filename; [2] "w+" [3] contents; [4] FD or nil

  if (!lua_isnil(L, -1)) {
    lua_remove(L, 2);  //dump "w+" attribute literal
    lua_replace(L, 1);
    // Stack [1] = FD; [2] contents
    file_write(L);
    // Stack [1] = FD; [2] contents; [3] result status
    lua_remove(L, 2);  //dump contents
    file_close(L);
    lua_remove(L, 1); // Dump FD leaving status as ToS
  }
  return 1;
}