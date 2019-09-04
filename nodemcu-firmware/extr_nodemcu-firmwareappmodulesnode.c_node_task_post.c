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
typedef  int /*<<< orphan*/  task_param_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int LUA_TFUNCTION ; 
 int LUA_TLIGHTFUNCTION ; 
 int LUA_TNUMBER ; 
 unsigned int TASK_PRIORITY_HIGH ; 
 unsigned int TASK_PRIORITY_MEDIUM ; 
 int /*<<< orphan*/  do_node_task ; 
 scalar_t__ do_node_task_handle ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 scalar_t__ luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 scalar_t__ task_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_post (unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int node_task_post( lua_State* L )
{
  int n = 1, Ltype = lua_type(L, 1);
  unsigned priority = TASK_PRIORITY_MEDIUM;
  if (Ltype == LUA_TNUMBER) {
    priority = (unsigned) luaL_checkint(L, 1);
    luaL_argcheck(L, priority <= TASK_PRIORITY_HIGH, 1, "invalid  priority");
    Ltype = lua_type(L, ++n);
  }
  luaL_argcheck(L, Ltype == LUA_TFUNCTION || Ltype == LUA_TLIGHTFUNCTION, n, "invalid function");
  lua_pushvalue(L, n);

  int task_fn_ref = luaL_ref(L, LUA_REGISTRYINDEX);

  if (!do_node_task_handle)  // bind the task handle to do_node_task on 1st call
    do_node_task_handle = task_get_id(do_node_task);

  if(!task_post(priority, do_node_task_handle, (task_param_t)task_fn_ref)) {
    luaL_unref(L, LUA_REGISTRYINDEX, task_fn_ref);
    luaL_error(L, "Task queue overflow. Task not posted");
  }
  return 0;
}