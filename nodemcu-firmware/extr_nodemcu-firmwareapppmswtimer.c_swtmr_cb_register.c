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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  suspend_policy; void* tmr_cb_ptr; } ;
typedef  TYPE_1__ cb_registry_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  CB_LIST_STR ; 
 int L_REGISTRY ; 
 int /*<<< orphan*/  add_to_reg_queue (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 TYPE_1__* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 size_t lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  push_swtmr_registry_key (int /*<<< orphan*/ *) ; 

void swtmr_cb_register(void* timer_cb_ptr, uint8 suspend_policy){
  lua_State* L = lua_getstate();
  if(!L){
    //Lua has not started yet, therefore L_REGISTRY is not available.
    //add timer cb to queue for later processing after Lua has started
    add_to_reg_queue(timer_cb_ptr, suspend_policy);
    return;
  }
  if(timer_cb_ptr){
    size_t cb_list_last_idx = 0;

    push_swtmr_registry_key(L);
    lua_rawget(L, L_REGISTRY);

    if(!lua_istable(L, -1)){
      //swtmr does not exist, create and add to registry
      lua_pop(L, 1);
      lua_newtable(L);//push new table for swtmr.timer_cb_list
      // add swtimer table to L_REGISTRY
      push_swtmr_registry_key(L);
      lua_pushvalue(L, -2);
      lua_rawset(L, L_REGISTRY);
    }

    lua_pushstring(L, CB_LIST_STR);
    lua_rawget(L, -2);

    if(lua_istable(L, -1)){
      //cb_list exists, get length of list
      cb_list_last_idx = lua_objlen(L, -1);
    }
    else{
      //cb_list does not exist in swtmr, create and add to swtmr
      lua_pop(L, 1);// pop nil value from stack
      lua_newtable(L);//create new table for swtmr.timer_cb_list
      lua_pushstring(L, CB_LIST_STR); //push name for the new table onto the stack
      lua_pushvalue(L, -2); //push table to top of stack
      lua_rawset(L, -4); //pop table and name from stack and register in swtmr
    }

    //append new timer cb ptr to table
    lua_pushnumber(L, cb_list_last_idx+1);
    cb_registry_item_t* reg_item = lua_newuserdata(L, sizeof(cb_registry_item_t));
    reg_item->tmr_cb_ptr = timer_cb_ptr;
    reg_item->suspend_policy = suspend_policy;
    lua_rawset(L, -3);

    //clear items pushed onto stack by this function
    lua_pop(L, 2);
  }
  return;
}