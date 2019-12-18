#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct jsonsl_state_st {scalar_t__ pos_begin; scalar_t__ pos_cur; } ;
struct TYPE_4__ {int /*<<< orphan*/  L; } ;
typedef  int /*<<< orphan*/  LUA_NUMBER ;
typedef  TYPE_1__ JSN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  get_state_buffer (TYPE_1__*,struct jsonsl_state_st*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void push_number(JSN_DATA *data, struct jsonsl_state_st *state) {
  lua_pushlstring(data->L, get_state_buffer(data, state), state->pos_cur - state->pos_begin);
  LUA_NUMBER r = lua_tonumber(data->L, -1);
  lua_pop(data->L, 1);
  lua_pushnumber(data->L, r);
}